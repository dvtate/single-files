#ifndef MENTIONS_OP_H
#define MENTIONS_OP_H

#include <string>
#include <vector>
#include <cinttypes>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <regex>
#include <functional>

#define MENTIONS_EXPR_RESOLUTIONS_

// fuzzywuzzy C++ library 
//   Probably this one: https://github.com/tmplt/fuzzywuzzy
#include "fuzz/fuzzywuzzy.hpp"
#include "fuzz/process.hpp"
#include "fuzz/utils.hpp"


class MentionsExpr {

public:
	typedef struct Value {
		enum type {
			AND   = 1,  // plane AND crash -
			OR    = 2,  // apple OR microsoft -
			NOT   = 3,  // crypto AND NOT bitcoin - excluding
			RXP   = 4,  // regular expression
			FUZZ  = 5,  // use fuzz to extract
			EXACT = 6,  // exact string match
		} type;

		// array indicies of argumnent(s)
		uint_fast16_t a;
		uint_fast16_t b;
	};

#ifdef MENTIONS_EXPR_RESOLUTIONS_
	std::vector<std::string> terms;   // fuzzy terms before processing
	std::vector<std::string> rxps; // regular expression texts
#endif

	std::vector<std::string> terms_p; // preprocessed terms for fuzzywuzzy
	std::vector<std::regex>  rxps_p; // compiled regular expression objects
	std::vector<std::string> eterms; // exact match terms
	std::vector<Value> exprs;

	Value expr;

	int tolerance;

	// compile expression into syntax tree
	MentionsExpr(std::string fmt, const int tolerance = 90) {
		this->tolerance = tolerance;

		fmt = _preprocess(fmt);
		//std::cout <<"after ppc:" <<fmt <<std::endl;
		uint_fast16_t offset = 0;
		uint_fast16_t term_ind = 0;

		std::vector<char> ops;

		do {
			// get token
			std::string t = _tokenizer(fmt, offset);
			//std::cout <<"token: '" <<t <<"'\toffset:" <<offset <<std::endl;
			//std::cout <<"  terms: " <<terms.size() <<"\texprs: " <<exprs.size() <<"\tops: " <<ops.size() <<std::endl;

			if (!t.size())
				continue;

			// not an operator
			if (!_is_operator(t[0])) {
				if (t[0] == '/') {
					std::cout <<"regex:";
					this->_empl_regex(t);
				} else if (t[0] == '"') {
					std::cout <<"exact:";
					this->_empl_exact(t.substr(1, t.size() - 2));
				} else {
					std::cout <<"fuzzy:";
					this->_empl_term(t);
				}

				std::cout <<this->exprs.size() - 1 <<"\t" <<t <<std::endl;

			// parens
			} else if (t[0] == '(' || ops.empty() || ops.back() == '(') {
				ops.emplace_back(t[0]);

			} else if (t[0] == ')') {
				while (ops.back() != '(' /* && ops.size() */) {
					std::cout <<"check back: " <<ops.back() <<std::endl;
					this->_empl_operator(ops.back());
					ops.pop_back();
				}
				ops.pop_back(); // '('

			// this assumes another value will be placed after it ... not safe
			} else if (t[0] == '!') {
				const Value v = { .type = Value::type::NOT , .a = this->exprs.size() };
				this->exprs.emplace_back(v);
			} else {
				this->_empl_operator(ops.back());
				ops.back() = t[0];
			}
			// std::cout <<"  terms: " <<terms.size() <<"\texprs: " <<exprs.size() <<"\tops: " <<ops.size() <<std::endl <<std::endl;

		} while (offset < fmt.size());

		for (short int i = ops.size() - 1; i >= 0; i--) {
			std::cout <<"cleanup op: " << ops[i] <<std::endl;
			this->_empl_operator(ops[i]);
		}

		expr = this->exprs.back();

	}

	bool parse(std::string text) {
		const std::string pp_text = fuzz::utils::full_process(text);

		std::function<bool(const Value)> parse_tree;
		parse_tree = [ this, pp_text, text, &parse_tree] (const Value tree) {
			switch (tree.type) {
				case Value::type::AND:
					std::cout <<"and ";
					return parse_tree(this->exprs[tree.a]) && parse_tree(this->exprs[tree.b]);
				case Value::type::OR:
					std::cout <<"or ";
					return parse_tree(this->exprs[tree.a]) || parse_tree(this->exprs[tree.b]);
				case Value::type::NOT:
					std::cout <<"not ";
					return !parse_tree(this->exprs[tree.a]);
				case Value::type::RXP: {
					std::cout << "regex(";
					const bool ret = std::regex_search(text, this->rxps_p[tree.a]);
					std::cout << this->rxps[tree.a] << ", " << ret << ") ";
					return ret;
				}
				case Value::type::FUZZ: {
					std::cout << "fuzzy(";
					const auto ret = fuzz::token_set_ratio(pp_text, this->terms_p[tree.a], false);
					std::cout << this->terms[tree.a] << ", " << ret << ") ";
					return ret >= this->tolerance;
				}
				case Value::type::EXACT:
					std::cout <<"exact(";
					const bool ret = text.find(this->eterms[tree.a]) != std::string::npos;
					std::cout <<this->eterms[tree.a] <<", " <<ret << ") ";
					return ret;
			}
		};

		return parse_tree(expr);

	}

	void print() {
		std::function<std::string(const Value)> str_tree;
		str_tree = [&] (const Value tree) {
			switch (tree.type) {
				case Value::type::AND:
					return "(" + str_tree(this->exprs[tree.a]) + " AND " + str_tree(this->exprs[tree.b]) + ")";
				case Value::type::OR:
					return "(" + str_tree(this->exprs[tree.a]) +" OR " + str_tree(this->exprs[tree.b]) + ")";

				case Value::type::NOT:
					return "NOT " + str_tree(this->exprs[tree.a]);
				case Value::type::RXP:
					return '/' + this->rxps[tree.a] + '/';
				case Value::type::EXACT:
					return '"' + this->eterms[tree.a] + '"';

				case Value::type::FUZZ:
					return this->terms[tree.a];
			}
		};

		std::cout << str_tree(this->expr);
	}

	void _empl_term(std::string term) {

#ifdef MENTIONS_EXPR_RESOLUTIONS_
		this->terms.emplace_back(term);
#endif
		this->terms_p.emplace_back(fuzz::utils::full_process(term));


		this->exprs.emplace_back(Value({
			.type = Value::type::FUZZ, .a = terms_p.size() - 1 }));

	}

	void _empl_regex(std::string rxp) {

#ifdef MENTIONS_EXPR_RESOLUTIONS_
		this->rxps.emplace_back(rxp);
#endif
		auto flags = std::regex::optimize;

		// check flags
		auto i = rxp.length() - 1;
		while (rxp[i] != '/') {
			if (rxp[i] == 'i')
				flags |= std::regex::icase;
			//else if (rxp[i] == 'm')
			//	flags |= std::regex_constants::multiline;
			else if (rxp[i] == 'b')
				flags |= std::regex::basic;
			else if (rxp[i] == 'e')
				flags |= std::regex::extended;
			else if (rxp[i] == 'a')
				flags |= std::regex::awk;
			else if (rxp[i] == 'c')
				flags |= std::regex::collate;
			i--;
		}

		this->rxps_p.emplace_back(std::regex(rxp));
		this->exprs.emplace_back(Value({
			.type = Value::type::RXP, .a = rxps_p.size() - 1 }));
	}

	void _empl_exact(const std::string& term) {
		this->eterms.emplace_back(term);
		this->exprs.emplace_back(Value({
			.type = Value::type::EXACT, .a = eterms.size() - 1 }));

	}
	void _empl_operator(char c) {
		Value v;

		v.type = c == ',' ? Value::type::OR : Value::type::AND;

		const auto s = this->exprs.size();

		v.a = s - 2;
		v.b = s - 1;

		this->exprs.emplace_back(v);
		std::cout <<(c == ',' ? "or" : "and") <<'(' << s-1 <<", " << s-2 <<"):" <<this->exprs.size() - 1;
	}


	static bool _is_operator(const char c) {
		static const char kws[] = ",;!()"; // keyword characters
		return strchr(kws, c) != NULL;
	}

	static void _substr_replace(std::string& str, const std::string& before, const std::string& after) {
		size_t index = 0;
		while (true) {
			// Locate the substring to replace
			index = str.find(before, index);
			if (index == std::string::npos)
				return;
			// Make the replacement
			str.replace(index, before.size(), after);
			// Advance index forward so the next iteration doesn't pick it up as well
			index += after.size();
		}
	}

	static std::string& _preprocess(std::string& str) {
		str += ' '; // shitty _tokenizer...
		_substr_replace(str, "AND", ";");
		_substr_replace(str, "OR", ",");
		_substr_replace(str, "NOT", "!");
		return str;
	}

	static bool _escaped(const  std::string& str, uint_fast16_t i) {
		uint8_t n = 0;
		while (i > 0 && str[i--] == '\\')
			n++;
		return n % 2;
	}

	static std::string _tokenizer(const std::string expr, uint_fast16_t& offset) {
		//
		while (isspace(expr[offset]))
			offset++;

		uint_fast16_t pre_offset = offset;

		bool quoted = false;


		while (offset < expr.size())
			if (_is_operator(expr[offset])) {
				// kw at start
				if (offset == pre_offset)
					return expr.substr(pre_offset, ++offset - pre_offset);
					// kw at end
				else
					return expr.substr(pre_offset, offset - pre_offset);

			} else if ((expr[offset] == '/' || expr[offset] == '"') && !_escaped(expr, offset - 1)) {
				offset++;
				quoted = !quoted;
			} else {
				offset++;
			}
		offset = expr.size();
		return expr.substr(pre_offset, expr.size() - pre_offset);

	}
};


#endif