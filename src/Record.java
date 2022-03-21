/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.time.LocalDate;
import java.util.Date;

/**
 * Defines what a records fieldnames are
 */
public class Record {

    // Data Fields
    private String personName;
    private LocalDate birthDate;
    private String birthPlaceLabel;
    private LocalDate deathDate;
    private String fieldLabel;
    private String genreLabel;
    private String instrumentLabel;
    private String nationalityLabel;
    private String thumbnail;
    private int wikiPageID;
    private String description;

    public Record(String personName, LocalDate birthDate, String birthPlaceLabel, LocalDate deathDate, String fieldLabel,
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
