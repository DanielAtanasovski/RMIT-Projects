/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.util.Date;

/**
 * Defines what a records fieldnames are
 */
public class Record {

    // Data Fields
    private String personName;
    private Date birthDate;
    private String birthPlaceLabel;
    private Date deathDate;
    private String fieldLabel;
    private String genreLabel;
    private String instrumentLabel;
    private String nationalityLabel;
    private String thumbnail;
    private int wikiPageID;
    private String description;

    public Record(String personName, Date birthDate, String birthPlaceLabel, Date deathDate, String fieldLabel,
                  String genreLabel, String instrumentLabel, String nationalityLabel,
                  String thumbnail, int wikiPageID, String description) {
        this.personName = personName;
        this.birthDate = birthDate;
        this.birthPlaceLabel = birthPlaceLabel;
        this.deathDate = deathDate;
        this.fieldLabel = fieldLabel;
        this.genreLabel = genreLabel;
        this.instrumentLabel = instrumentLabel;
        this.nationalityLabel = nationalityLabel;
        this.thumbnail = thumbnail;
        this.wikiPageID = wikiPageID;
        this.description = description;
    }


    public Byte[] toBinary() {
        return null;
    }


}
