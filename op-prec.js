function leftAssociative(t) {

	const cp_node = n => {
		n = JSON.parse(JSON.stringify(t));
		n.members = [];
		return n;
	}

	let nt = cp_node(t);
	nt.members = [];


	let ret = nt;
	for (let i = 0; i < t.members.length; i++) {
		nt.members.push(t.members[i]);
		nt.members.push(cp_node(t));
//		console.log(nt.members);
		nt = nt.members[1];
	}

	return ret;

}



let t = {
	token: "+",
	members: [
		{
			token : "5",
			members: []		
		}, {
			token : "*",
			members: [ {
					token: "5",
					members: [],
				}, {
					token: "10",
					members: [],
				} ],
		}, {
			token : "\"ffffff\"",
			members : []
		},
	]
};


console.log(JSON.stringify(leftAssociative(t)));

function rightAssociative(t) {

	const cp_node = n => {
		n = JSON.parse(JSON.stringify(t));
		n.members = [];
		return n;
	}

	let nt = cp_node(t);
	nt.members = [];

	const ret = nt;

	for (let i = t.members.length; i >= 0; i--) {
		console.log(nt);
		nt.members.push(cp_node(t));
		nt.members.push(t.members[i]);
		nt = nt.members[1];
	}	
	
	return ret;
}



console.log(JSON.stringify(rightAssociative(t)));
