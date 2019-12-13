package org.jsflab;

import java.util.Date;

public class Card {
    
    private int number;
    private String name;
    private String lastName;
    private String middleName;
    private String passport;
    private String adress;
    private Date createDate;
    private Date birth;
    private int ssn;
    private boolean isPay;
    private String allergy;

    public Card(int number, String name, String lastName, String middleName, String passport, String adress, Date createDate, Date birth, int ssn, boolean isPay, String allergy) {
        this.number = number;
        this.name = name;
        this.lastName = lastName;
        this.middleName = middleName;
        this.passport = passport;
        this.adress = adress;
        this.createDate = createDate;
        this.birth = birth;
        this.ssn = ssn;
        this.isPay = isPay;
        this.allergy = allergy;
    }

    public Card() {
        
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getMiddleName() {
        return middleName;
    }

    public void setMiddleName(String middleName) {
        this.middleName = middleName;
    }
    
    public String getPassport() {
        return passport;
    }

    public void setPassport(String passport) {
        this.passport = passport;
    }

    public String getAdress() {
        return adress;
    }

    public void setAdress(String adress) {
        this.adress = adress;
    }

    public Date getCreateDate() {
        return createDate;
    }

    public void setCreateDate(Date createDate) {
        this.createDate = createDate;
    }

    public Date getBirth() {
        return birth;
    }

    public void setBirth(Date birth) {
        this.birth = birth;
    }

    public int getSsn() {
        return ssn;
    }

    public void setSsn(int ssn) {
        this.ssn = ssn;
    }

    public boolean isIsPay() {
        return isPay;
    }

    public void setIsPay(boolean isPay) {
        this.isPay = isPay;
    }

    public String getAllergy() {
        return allergy;
    }

    public void setAllergy(String allergy) {
        this.allergy = allergy;
    }

}
