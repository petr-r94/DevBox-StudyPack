127.0.0.1:8080/base
127.0.0.1:8080/ServletLab
127.0.0.1:8080/ServletLab/base

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




INSERT into PatientCards(Name, LastName) VALUES('Иван','Иванов');
INSERT into PatientCards(Name, LastName) VALUES('Сидор','Сидоров');