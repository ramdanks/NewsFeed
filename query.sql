
CREATE TABLE Account (
	username CHAR(20) PRIMARY KEY,
	password CHAR(32) NOT NULL,
	email CHAR(50) NOT NULL,
	dob DATE NOT NULL,
	displayname CHAR(30),
	bio CHAR(100),
	createTime TIMESTAMP NOT NULL DEFAULT NOW()::TIMESTAMP
);


CREATE TABLE Follow (
	id SERIAL PRIMARY KEY,
	sender CHAR(20) NOT NULL REFERENCES Account(username),
	receiver CHAR(20) NOT NULL REFERENCES Account(username),
	logTime TIMESTAMP NOT NULL DEFAULT NOW()::TIMESTAMP
);

CREATE TABLE Flag (
	id SERIAL PRIMARY KEY,
	label CHAR(20) NOT NULL,
	owner CHAR(20) NOT NULL REFERENCES Account(username)
);

CREATE TABLE Feed (
	id SERIAL PRIMARY KEY,
	actor CHAR(20) NOT NULL REFERENCES Account(username),
	text CHAR(200) NOT NULL,
	fid INT NOT NULL REFERENCES Flag(id),
	postTime TIMESTAMP NOT NULL DEFAULT NOW()::TIMESTAMP 
);

CREATE TYPE Service AS ENUM ('Message', 'Team', 'happy');

CREATE TABLE Billing (
	id SERIAL PRIMARY KEY,
	buyer CHAR(20) NOT NULL REFERENCES Account (username),
	logTime TIMESTAMP NOT NULL DEFAULT NOW()::TIMESTAMP,
);

INSERT INTO Follow(sender, receiver) VALUES('%s', '%s');
DELETE FROM Follow WHERE sender='%s' AND receiver='%s';

UPDATE Account SET bio='%s' WHERE username='%s';
UPDATE Account SET displayname='%s' WHERE username='%s';

SELECT id FROM Flag WHERE label='%s' AND owner='%s';
SELECT label FROM Flag WHERE owner='%s';
INSERT INTO Flag(label,owner) VALUES('%s','%s');
DELETE FROM Flag WHERE label='%s' AND owner='%s';

SELECT displayname, bio FROM Account WHERE username='%s';
SELECT receiver FROM Follow WHERE sender='%s';

INSERT INTO Feed(actor,text,fid) VALUES ('%s', '%s', '%u');
SELECT * FROM Feed WHERE actor='%s';