/******************************************************************************

Complete implementation of SecurityLookup class defined below.

This class maintains Security objects and provides methods for their lookup
via Security attributes.

    • Every Security object has a unique id (id_)
    • Every Security object has a unique symbol (symbol_)
    • Every Security object has a (potentially non-unique) channel id (channel_)

You are responsible for implementing the following methods:

    Security GetSecurity(int id) const

        Return Security object with given id or default (invalid) Security object if not found

    Security GetSecurity(const std::string& symbol) const

        Return Security object with given symbol or default (invalid) Security object if not found

    Securities GetSecurities(int channel) const

        Returns all Security objects with given channel value
        or an empity List of Security objects, if not matching securities are found

    void SaveSecurity(const Security& sec)

        Add a Security object to the lookup instance

        If a Security with a given id already exists:
            • Update Security with new channel id

                Before state:
                    Security: 1, "MSFT", 1
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

                Mutations:
                    Save Security: 1, "MSFT, 2

                After state:
                    Security: 1, "MSFT", 2
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

            • Update Security with new symbol

                Before state:
                    Security: 1, "MSFT", 1
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

                Mutations:
                    Save Security: 1, "AAPL", 1

                After state:
                    Security: 1, "AAPL", 1
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

            • Throw std::runtime_error if symbol is being used by an another Security

                Before state:
                    Security: 1, "MSFT", 1
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

                Mutations:
                    Save Security 1, "GOOG", 1
                    <<< Exception! >>>

                After state:
                    Security: 1, "MSFT", 1
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

            • Do not throw std::runtime_error if symbol is in use by the same Security (NOOP)

                Before state:
                    Security: 1, "MSFT", 1
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

                Mutations:
                    Save Security 1, "MSFT", 1

                After state:
                    Security: 1, "MSFT", 1
                    Security: 2, "TSLA", 1
                    Security: 3, "GOOG", 1

        If a Security with a given id does not exist:
            • Save new Security

                Before state:
                    Security: 1, "MSFT", 1

                Mutations:
                    Save Security: 2, "TSLA", 2

                After state:
                    Security: 1, "MSFT", 1
                    Security: 2, "TSLA", 2


The expected number of Security objects within this Lookup is on the order of
10s of millions.  The choice of underlying data structures must ensure
efficient lookups.

Note:
     - Feel free to use a text editor or IDE of your choice to do this instead.
     - If you do, simply just copy-paste your code here when you're done.
     - You are free to add any supporting helper functions, data types, or
       structures you wish.
     - You may make use of STL data structures and algorithms
     - main function has been provided to make code run inside Rextester Web
       IDE. It is not required to be part of the submission and will not be
       graded.

******************************************************************************/

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>

#include <iostream> // for testing

struct Security
{
	uint32_t id_;
	std::string symbol_;
	uint16_t channel_;

	Security()
			: id_{ 0 }
			, channel_{ 0 }
	{}

	Security(uint32_t id, std::string symbol, uint16_t channelId)
			: id_(id)
			, symbol_(symbol)
			, channel_(channelId)
	{}

	bool IsValid() const { return id_ != 0; }
};

using Securities = std::vector<Security>;

class SecurityLookup
{

	// assuming the goal is fast lookup time without memory constraints or speed of indexing
public:
	Security GetSecurity(int id) const
	{
		try {
			const auto i = id_lookup_.at(id);
			return instances_[i];
		} catch (const std::out_of_range& e) {
			return Security();
		}
	}

	Security GetSecurity(const std::string& symbol) const
	{
		try {
			const auto i = symbol_lookup_.at(symbol);
			return instances_[i];
		} catch (const std::out_of_range& e) {
			return Security();
		}
	}

	Securities GetSecurities(int channel) const
	{
		try {
			const auto& els = channel_lookup_.at(channel);
			Securities ret;
			ret.reserve(els.size());
			for (const int64_t i : els)
				if (i > 0)
					ret.push_back(instances_[i]);

			return ret;
		} catch (const std::out_of_range& e) {
			return Securities();
		}
	}

	void SaveSecurity(const Security& sec)
	{

		const Security dup = this->GetSecurity(sec.id_);


		// need to update channel/symbol indexing
		const bool ud_channel = dup.IsValid() && dup.channel_ != sec.channel_;
		const bool ud_symbol = dup.IsValid() && dup.symbol_ != sec.symbol_;

		instances_.emplace_back(sec);

		// index for id search
		const uint32_t ind = instances_.size() - 1;
		id_lookup_[sec.id_] = ind;

		// no duplicate symbols
		if (!ud_channel && GetSecurity(sec.symbol_).IsValid())
			throw std::runtime_error("duplicate symbol");

		// index by symbol
		if (ud_symbol)
			symbol_lookup_.erase(dup.symbol_);
		symbol_lookup_[sec.symbol_] = ind;

		const auto it = channel_lookup_.find(sec.channel_);
		if (it == channel_lookup_.end())
			channel_lookup_.insert({ sec.channel_, { ind, } });
		else
			it->second.emplace_back(ind);


		if (ud_channel) {
			// delete old channel entry
			uint32_t dup_ind = id_lookup_.at(dup.id_);
			std::vector<int64_t>& cl = channel_lookup_.at(sec.channel_);
			const auto el = std::find(cl.begin(), cl.end(), dup_ind);
			if (el != cl.end())
				*el = -1; // mark as invalid
			// cl.erase(el);

		}
	}

	// TODO: rehash member function that
private:
	// all securities
	Securities instances_;

	// using unordered map because O(1) lookup time

	// for small datasets using std::map would be better
	//   im assuming we're looking at a large dataset
	std::unordered_map<uint32_t, uint32_t> id_lookup_;
	std::unordered_map<std::string, uint32_t> symbol_lookup_;
	std::unordered_map<uint16_t , std::vector<int64_t>> channel_lookup_;

	// could potentially use a sparse vector (ie- std::flat_map)

};

int main ()
{
	SecurityLookup lookup;
	lookup.SaveSecurity(Security(1,	"MSFT",	1));
	lookup.SaveSecurity(Security(2,	"AAPL",	2));
	lookup.SaveSecurity(Security(3,	"AMD",	1));
	lookup.SaveSecurity(Security(1, "RPC",	2)); // change msft channel 1->2
	lookup.SaveSecurity(Security(4, "SPY",	1));
	lookup.SaveSecurity(Security(5, "BYND",	2));
	lookup.SaveSecurity(Security(5, "VSLR",	2)); // change symbol bynd->vslr

	std::cout <<"should be vslr:" <<lookup.GetSecurity(1).symbol_ <<std::endl;
	std::cout <<"should be 4:" <<lookup.GetSecurity("MSFT").id_ <<std::endl;
	std::cout <<"c1: " <<lookup.GetSecurities(1).size()  <<std::endl;
	std::cout <<"c2: " <<lookup.GetSecurities(2).size()  <<std::endl;

}
