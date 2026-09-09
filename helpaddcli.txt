Add a col to a table of sqlite

For example, modify the Vergifac Cli table by adding a col Siret number after col `add4`
https://github.com/pap71/vergifac.git
SQLite can add a column, but only in the last position.

Par exemple modifier la table Cli de vergifac en ajoutant une col Siret apres la col add4
 https://github.com/pap71/vergifac.git
sqlite peut rajoutter une col mais uniquement en dernière position.


CREATE TABLE Cli (
	Clefacc VARCHAR(12),
	Type VARCHAR(2),
	Add1 VARCHAR(50),
	Add2 VARCHAR(50),
	Add3 VARCHAR(50),
	Pays VARCHAR(4),
	Codpos VARCHAR(8),
	Add4 VARCHAR(40),
insert ->                   Siret VARCHAR(16),
	Datcre VARCHAR(12),
	Datmod VARCHAR(12),
	Tel VARCHAR(18),
	Mail VARCHAR(40),
	Notes BLOB
);

Copy the dbvergifac.db database from vergifac, renaming it to dbvergi-old.db.
dbvergi-old.db becomes a backup of the original database and the input for the addcol program.

copier la base dbvergifac.db de vergifac renommée en dbvergi-old.db
dbvergi-old.db devient sauvegarde de la db d'origine et entrée du prog addcol

preparing dbvergifac.db with sqlite3 in a terminal

preparation de dbvergifac.db avec sqlite3 dans un terminal

>> sqlite3 dbvergifac.db < recretabcli

    The Cli table is deleted
    and recreated with the new SIRET information
    but all the Cli data has disappeared.
    la table Cli est supprimée 
    et recrée avec la nouvelle info siret
    mais toutes les données Cli ont disparus.

The addcol program will restore the table from dbvergi-cold.db
le programme addcol va restaurer la table à partir de dbvergi-cold.db

>> ./addcol dbvergi-old.db dbvergifac.db
