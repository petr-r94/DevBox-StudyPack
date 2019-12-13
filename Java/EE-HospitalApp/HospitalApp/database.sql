127.0.0.1:8080/HospitalApp


CREATE TABLE HospitalChambers (
  Floor       integer NOT NULL, 
  Number      integer NOT NULL, 
  Capacity    integer NOT NULL,
  ID_Chamber  SERIAL PRIMARY KEY NOT NULL
);
  
CREATE TABLE PatientCards (
  Number                    SERIAL PRIMARY KEY NOT NULL, 
  Name                      varchar(20) NOT NULL, 
  LastName                  varchar(20) NOT NULL, 
  MiddleName                varchar(20), 
  Passport                  integer[10] UNIQUE,
  Adress                    text,  
  CreateDate                date,
  Birth       				date,
  SSN   					integer UNIQUE, 
  IsPay                     boolean DEFAULT false, 
  Allergy                   text
);
  
CREATE TABLE TreatmentPeriods (
  ReceiptDate               date, 
  ReceiptDateReason  		text, 
  DischargeSummary          text, 
  DischargeDate             date, 
  PatientCards_Number 	    integer NOT NULL,
  ID_Period                 SERIAL PRIMARY KEY NOT NULL
);

CREATE TABLE MtoM (
  Chambers_id integer NOT NULL, 
  Periods_id integer NOT NULL,
  PRIMARY KEY(Chambers_id, Periods_id)
);

CREATE TABLE DiagResults (
  Conclusion             text, 
  Assignments            text, 
  Date                   date, 
  Procedures             varchar(30), 
  PatientCards_Number    integer NOT NULL
);
  
ALTER TABLE DiagResults ADD CONSTRAINT examinee FOREIGN KEY(PatientCards_Number) REFERENCES PatientCards(Number);
ALTER TABLE TreatmentPeriods ADD CONSTRAINT indicate FOREIGN KEY(PatientCards_Number) REFERENCES PatientCards(Number);
ALTER TABLE MtoM ADD CONSTRAINT fk_MtoM__Chambers foreign key(Chambers_id) REFERENCES HospitalChambers(ID_Chamber);
ALTER TABLE MtoM ADD CONSTRAINT fk_MtoM__Periods foreign key(Periods_id) REFERENCES TreatmentPeriods(ID_Period);




INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (1, 'Иван', 'Иванов', 'Иванович', '{2,9,1,9,4,5,6,2,3,4}', 'Bangladesh, Vamira St 56/23', '2015-12-06', '1998-03-01', 123456, false, 'Novokoin');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (2, 'Сидор', 'Сидоров', 'Сидорович', '{2,9,1,9,4,5,8,2,6,4}', 'Paris, mirasi St, 25-98', '2009-02-01', '1999-04-02', 124589, false, '-');

INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (3, 'Jack', 'London', '-', '{2,9,1,9,1,1,1,2,6,4}', 'London, graph St, 11/25-26', '2016-03-04', '2004-12-11', 673467, false, 'Syndexetex');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (4, 'Тимофей', 'Мурашов', 'Тимофеевич', '{2,9,10,4,4,8,2,6,1}', 'Moscow, Kashirskoe St, 21-5', '2011-01-03', '2015-11-12', 23412467, true, '-');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (5, 'Smith', 'Kaize', 'Fahreignokz', '{2,9,1,9,4,5,6,2,3,44}', 'Roichi, Dexs St, 106/23', '2015-11-06', '1998-03-01', 12345809, false, 'Dimedrol');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (6, 'Daneline', 'Firtzhei', 'Nodoiseme', '{2,9,1,9,4,5,6,2,1,14}', 'FExcedi ,Maut St, 1114', '2015-11-26', '1998-03-01', 234568, true, '-');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (7, 'Xen', 'Fovad', '-', '{2,9,1,9,4,0,8,2,6,4}', 'Paris, kysmiz St, 24-943', '2014-02-01', '1999-01-02', 245670, false, '-');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (8, 'Xen', 'Richov', '-', '{2,9,1,9,4,5,8,2,6,5}', 'Paris, kysmiz St, 25-944', '2011-04-01', '1999-01-22', 124576769, false, 'Hexon, Melizodrol');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (9, 'Zelda', 'Irish', 'Risadz', '{3,9,1,9,4,5,8,0,6,0}', 'Wein,barmikeiz St, 304', '2016-02-01', '1985-01-05', 876523, false, 'Tanhiboz');
INSERT INTO patientcards (number, name, lastname, middlename, passport, adress, createdate, birth, ssn, ispay, allergy) VALUES (10, 'Sharz', 'Seniopal', 'Humerig', '{2,8,8,9,4,8,8,2,6,5}', 'Cyprys, Larnaca 45-98', '2008-07-11', '1999-01-22', 129998742, false, 'Hexon');


ALTER TABLE patientcards ALTER COLUMN passport TYPE varchar
