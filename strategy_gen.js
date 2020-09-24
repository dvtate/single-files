const request = require("request-promise-native");

const token = "dXB2dCOYn81sXAj/D2EU5esEHaneMoPxaoC5OwFBmVYFDBOLhWbDIxZcbTXBnLKs";

const account = 2176196971820114;

const stocks = ["aapl", "abc", "sunw", "msft", "tsla", "f", "plug", "flng", 
				"lyft", "work", "uber", "zm", "levi"];

const fiats = ["usd", "cny", "eur", "aud", "cad", "mxn", "jpy", "kwd", "usd", "usd"];

const coins = ["bitcoin-cash", "etherium", "litecoin", "0x", "basic-attention-token",
			   "usd-coin", "zcash", "dai", "augur", "ripple", "eos"];

const twitter_users = ["realDonaldTrump", "dvtate0", "stratty_x", "elonmusk",
					   "tim_cook", "cnn", "theonion", "nasa", "andrewyang", "barackobama", "potus"];

const terms = ["china", "win", "trade", "war", "climate", "congress", "economy", 
			   "hong kong", "free" ,"green", "brazil", "new", "violent", "loss",
			   "trump", "china", "leader", "condemn", "strike"];

function rss() {
	const feeds = [
		"https://reddit.com/r/corkimains/new/.rss",
		"https://www.reddit.com/r/pan/new/.rss",			
		"https://www.reddit.com/r/science/new/.rss",
		"https://www.reddit.com/r/wellthatsucks/new/.rss",
		"https://www.reddit.com/r/leagueoflegends/new/.rss",
	];
}

let types = {};

const generators = [
	function twitter_user() {
		types["twitter_user-mentions"] = (types["twitter_user-mentions"] || 0) + 1;
		const u = twitter_users[Math.floor(Math.random() * twitter_users.length)];
		const t = terms[Math.floor(Math.random() * terms.length)];
		return `"${u}" twitter_user ["${t}"] mentions`;
	},

	function news_publisher(){
		types["news_publisher-mentions"] = (types["news_publisher-mentions"] || 0) + 1;
		const publishers = ["cnn", "nytimes", "fox", "huffpo", "reuters"];
		const p = publishers[Math.floor(Math.random() * publishers.length)];
		const t = terms[Math.floor(Math.random() * terms.length)];
		return `{"publisher":"${p}","mentions_title":"${t}"} news`;
	},
	function news_topic() {
		types["news_topic-mentions"] = (types["news_topic-mentions"] || 0) + 1;
		const topics = ["green", "business", "macroeconomy", "auto", "world", "us", "russia", "china"];
		const tpc = topics[Math.floor(Math.random() * topics.length)];
		const t = terms[Math.floor(Math.random() * terms.length)];
		return `{"topic":"${tpc}","mentions_title":"${t}"} news`;
	
	},

	function news_category() {
		types["news_category-mentions"] = (types["news_category-mentions"] || 0) + 1;
		const categories = ["leftwing", "nerd", "web", "paper", "tv"];
		const cat = categories[Math.floor(Math.random() * categories.length)];
		const t = terms[Math.floor(Math.random() * terms.length)];
		return `{"category":"${cat}","mentions_title":"${t}"} news`;
	}, 

	function news_all() {
		types["news_all-mentions"] = (types["news_all-mentions"] || 0) + 1;
		const t = terms[Math.floor(Math.random() * terms.length)];
		return `{"mentions_title":"${t}"} news`;
	},

	function price() {
		types["price-threshold"] = (types["price-threshold"] || 0) + 1;
		const crypto = Math.random() > 0.4;
		const syms = crypto ? coins : stocks;
		const sym = syms[Math.floor(Math.random() * syms.length)];
		return `now "${sym}" ${crypto ? "exchange" : "price"} ${Math.random() * 800
			} ${Math.random() > 0.5 ? '>' : '<'}`;
	},

	function price_change() {
		types["price-change"] = (types["price-change"] || 0) + 1;
		const crypto = Math.random() > 0.4;
		const syms = crypto ? coins : stocks;
		const sym = syms[Math.floor(Math.random() * syms.length)];
		const diff = Math.random() > 0.5 ? '>' : '<';
		const time = "" + Math.round(Math.random() * 30) + (["mins", "hrs", "days"][Math.floor(Math.random() * 3)]);
		const percent = Math.random() > 0.5;
		if (percent) { // percent price change
			const val = (Math.random() - 0.5) / 4;
			return `now "${sym}" price now "${time}" date - "${sym}" price - now "${sym}" price / ${val} ${diff}`;			
		} else { // usd price change 
			const val = (Math.random() - 0.5) * 4;
			return `now "${sym}" price now "${time}" date - "${sym}" price - ${val} ${diff}`;
		}

		return "0";
	},

	function xrate() {
		types["xrate-threshold"] = (types["xrate-threshold"] || 0) + 1;
		const l1 = Math.random() > 0.4 ? coins : fiats;
		const l2 = Math.random() > 0.4 ? coins : fiats;
		const c1 = l1[Math.floor(Math.random() * l1.length)];
		const c2 = l2[Math.floor(Math.random() * l2.length)];
		const cmp = Math.random() > 0.5;
		const v = Math.random() * 4;
		return `now "${c1}" exchange now "${c2}" exchange / ${v} ${cmp}`
	},

	function xrate_change() {
		const l1 = Math.random() > 0.4 ? coins : fiats;
		const l2 = Math.random() > 0.4 ? coins : fiats;
		const c1 = l1[Math.floor(Math.random() * l1.length)];
		const c2 = l2[Math.floor(Math.random() * l2.length)];
		const time = "" + Math.round(Math.random() * 30) + (["mins", "hrs", "days"][Math.floor(Math.random() * 3)]);
		const cmp = Math.random() > 0.5 ? '>' : '<';
		const percent = Math.random() > 0.4;
		if (percent) {
			types["xrate-change-percent"] = (types["xrate-change-percent"] || 0) + 1;
			return `now "${c1}" exchange now "${c2}" exchange / now "${time}" date - "${c1}" exchange now "${time}" date - "${c2}" exchange / - now "${c1}" exchange now "${c2}" exchange / / ${(Math.random() - 0.5) / 4} ${cmp}`;
		} else {
			types["xrate-change-cur"] = (types["xrate-change-cur"] || 0) + 1;
			return `now "${c1}" exchange now "${c2}" exchange / now "${time}" date - "${c1}" exchange now "${time}" date - "${c2}" exchange / - ${(Math.random() - 0.5) * 5} ${cmp}`;
		}
	},

/* no longer using
	function gnews_topic() {
		
		types["gnews-topic-text-mentions"] = (types["gnews-topic-text-mentions"] || 0) + 1;
		const tpc = ["WORLD", "SCIENCE", "BUSINESS", "TECHNOLOGY"][Math.floor(Math.random() * 4)];
		const t = terms[Math.floor(Math.random() * terms.length)];
		return `"${tpc}" gnews_topic "text" scrape_news ["${t}"] mentions`;
	},
	function gnews_search() {
		types["gnews-search-text-mentions"] = (types["gnews-search-text-mentions"] || 0) + 1;
		const s = terms[Math.floor(Math.random() * terms.length)];
		const t = terms[Math.floor(Math.random() * terms.length)];
		return `"${s}" gnews_search "text" scrape_news ["${t}"] mentions`;
	},
*/

/*
	function crossover() {
		return '0';
	},
*/


	/// TODO: sector-price-change
];


async function makeStrategy() {
	function makeConditionExpr() {
		let conds = [];
		for (let i = Math.random()*6; i > 0; i--)
			conds.push(generators[Math.floor(Math.random() * generators.length)]());
		let ret = conds.join(' ');
		for (let i = 1; i < conds.length; i++)
			ret += Math.random() > 0.5 ? ' and' : ' or';
		return ret;
	}
	
/*
	try {
		await request("http://api.strattyx.work/strategy/create", {
			method: "POST",
			json: {
				"enterprise": false,
				"symbol": stocks[Math.floor(stocks.length * Math.random())],
				"symbolType": "equity",
				"buyCondition": makeConditionExpr(),
				"sellCondition": makeConditionExpr(),
				"description": "stress testing",
				"buyQuantity": 1,
				"sellQuantity": 1,
				"buyUnit": "shares",
				"sellUnit": "shares",
				"accountId": account,
				"duration": 21600000
			},
			headers: {
				"authorization": "Bearer " + token,
			}
		})
	catch (e) {
		console.error(e);
	}
*/

/*
	try {	
		return await request("http://api.strattyx.work/strategy/preprocess/nl?condition=" + makeConditionExpr())
	} catch(e) { 
		console.error(e);
	}
*/
}

let arr = [];
for (let i = 0; i < 20; i++) 
	arr.push(makeStrategy())

Promise.all(arr).then(console.log).catch(console.error)

console.log(types);
