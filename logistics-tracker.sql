
CREATE TABLE Users (
	phoneNumber VARCHAR(20) PRIMARY KEY,
	name VARCHAR(64) NOT NULL,
	email UNIQUE,
);

-- Birds (or potentially other things in the future) which have been found
--  Should be marked as accessible
CREATE TABLE Finds (
	-- Unique Identifier
	findId BIGINT UNSIGNED PRIMARY KEY,
	
	-- Who made the find?
	foundByUser VARCHAR(20) REFERENCES Users.phoneNumber,

	-- Location where found
	location VARCHAR(128) NOT NULL,
	
	-- Epoch ms when found
	ts BIGINT UNSIGNED NOT NULL,
	
	-- short summary of the find (ie - species, status, etc.)
	description VARCHAR(128) NOT NULL,
	
	-- 
	status VARCHAR(128) NOT NULL,
	
	-- More detailed notes/relevant info
	notes TEXT DEFAULT NULL,
	
	-- Where should it be moved to?
	targetDest VARCHAR(128) DEFAULT NULL,
	
	-- 
	priority ENUM('low', 'medium', 'high'),
);


CREATE TABLE FindMovements (

);

CREATE TABLE FindTransfers (
	findId BIGINT REFERENCES Finds,
	ts BIGINT NOT NULL,
	fromUserId VARCHAR(20) DEFAULT NULL,
	toUserId VARCHAR(20) DEFAULT NULL,
	
);

CREATE TABLE FindStatusChange (

);

