/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.Collections;

/**
 * Defines what a records fieldnames are
 */
public class Record {

    // If we were to accommodate all data within with longest works

    // Theoretical Maximum byte values
    private static int maxPersonNameBytes       = 70;
    private static int maxBirthPlaceLabelBytes  = 158;
    private static int maxFieldLabelBytes       = 242;
    private static int maxGenreLabelBytes       = 386;
    private static int maxInstrumentLabelBytes  = 545;
    private static int maxNationalityLabelBytes = 119;
    private static int maxThumbnailBytes        = 223;
    private static int maxDescriptionBytes      = 466;
    // 2229 Total Bytes

    private static String nullTerminator = "\u0000";

    // Data Fields
    private final byte[]    recordBytes;
    private final LocalDate birthDate; // .toEpochDay 8 bytes
    private final LocalDate deathDate; // .toEpochDay 8 bytes
    private final int       wikiPageID; // 4 bytes
    private       String    personName;
    private       String    birthPlaceLabel;
    private       String    fieldLabel;
    private       String    genreLabel;
    private       String    instrumentLabel;
    private       String    nationalityLabel;
    private       String    thumbnail;
    private       String    description;

    public Record(String personName, LocalDate birthDate, String birthPlaceLabel, LocalDate deathDate,
                  String fieldLabel,
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
        recordBytes = calculateBytes();
    }

    public Record(byte[] inputBytes) {
        int offset = 0;

        // Dates
        ByteBuffer byteBuffer = ByteBuffer.wrap(inputBytes, 0, Long.BYTES);
        this.birthDate = LocalDate.ofEpochDay(byteBuffer.getLong());
        offset += Long.BYTES;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, Long.BYTES);
        this.deathDate = LocalDate.ofEpochDay(byteBuffer.getLong());
        offset += Long.BYTES;

        // WikiPageID
        byteBuffer = ByteBuffer.wrap(inputBytes, offset, Integer.BYTES);
        this.wikiPageID = byteBuffer.getInt();
        offset += Integer.BYTES;

        // Strings
        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxPersonNameBytes);
        byte[] bytes = Arrays.copyOfRange(byteBuffer.array(), byteBuffer.position(), byteBuffer.remaining());
        this.personName = new String(bytes).trim();
        offset += maxPersonNameBytes;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxBirthPlaceLabelBytes);
        this.birthPlaceLabel = new String(byteBuffer.array());
        offset += maxBirthPlaceLabelBytes;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxFieldLabelBytes);
        this.fieldLabel = new String(byteBuffer.array());
        offset += maxFieldLabelBytes;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxGenreLabelBytes);
        this.genreLabel = new String(byteBuffer.array());
        offset += maxGenreLabelBytes;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxInstrumentLabelBytes);
        this.instrumentLabel = new String(byteBuffer.array());
        offset += maxInstrumentLabelBytes;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxNationalityLabelBytes);
        this.nationalityLabel = new String(byteBuffer.array());
        offset += maxNationalityLabelBytes;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxThumbnailBytes);
        this.thumbnail = new String(byteBuffer.array());
        offset += maxThumbnailBytes;

        byteBuffer = ByteBuffer.wrap(inputBytes, offset, maxDescriptionBytes);
        this.description = new String(byteBuffer.array());
        offset += maxDescriptionBytes;

        recordBytes = calculateBytes();
    }

    // Function to modify the maximum bytes of records
    public static void setMaxBytes(int personName, int birthPlace, int fieldLabel, int genreLabel,
                                   int instrumentLabel, int nationalityLabel, int thumbnail, int description) {
        maxPersonNameBytes = personName;
        maxBirthPlaceLabelBytes = birthPlace;
        maxFieldLabelBytes = fieldLabel;
        maxGenreLabelBytes = genreLabel;
        maxInstrumentLabelBytes = instrumentLabel;
        maxNationalityLabelBytes = nationalityLabel;
        maxThumbnailBytes = thumbnail;
        maxDescriptionBytes = description;
    }

    public static int getMaxBytes() {
        return maxPersonNameBytes + maxBirthPlaceLabelBytes + maxFieldLabelBytes + maxGenreLabelBytes +
               maxInstrumentLabelBytes + maxNationalityLabelBytes + maxThumbnailBytes + maxDescriptionBytes +
               Long.BYTES + Long.BYTES + Integer.BYTES;
    }

    public LocalDate getBirthDate() {
        return this.birthDate;
    }

    public int getWikiPageID() {
        return wikiPageID;
    }

    public String getPersonName() {
        return this.personName.trim();
    }

    public String getThumbnail() {
        return thumbnail.trim();
    }

    private byte[] calculateBytes() {
        ByteArrayOutputStream recordBytes = new ByteArrayOutputStream();

        // Set Strings to Maximum
        if (this.personName.getBytes(StandardCharsets.UTF_8).length < maxPersonNameBytes)
            this.personName = this.personName + String.join("", Collections.nCopies(
                    maxPersonNameBytes - this.personName.getBytes(StandardCharsets.UTF_8).length, nullTerminator));

        if (this.birthPlaceLabel.getBytes(StandardCharsets.UTF_8).length < maxBirthPlaceLabelBytes)
            this.birthPlaceLabel = this.birthPlaceLabel + String.join("", Collections.nCopies(
                    maxBirthPlaceLabelBytes - this.birthPlaceLabel.getBytes(StandardCharsets.UTF_8).length,
                    nullTerminator));

        if (this.fieldLabel.getBytes(StandardCharsets.UTF_8).length < maxFieldLabelBytes)
            this.fieldLabel = this.fieldLabel + String.join("", Collections.nCopies(
                    maxFieldLabelBytes - this.fieldLabel.getBytes(StandardCharsets.UTF_8).length, nullTerminator));

        if (this.genreLabel.getBytes(StandardCharsets.UTF_8).length < maxGenreLabelBytes)
            this.genreLabel = this.genreLabel + String.join("", Collections.nCopies(
                    maxGenreLabelBytes - this.genreLabel.getBytes(StandardCharsets.UTF_8).length, nullTerminator));

        if (this.instrumentLabel.getBytes(StandardCharsets.UTF_8).length < maxInstrumentLabelBytes)
            this.instrumentLabel = this.instrumentLabel + String.join("", Collections.nCopies(
                    maxInstrumentLabelBytes - this.instrumentLabel.getBytes(StandardCharsets.UTF_8).length,
                    nullTerminator));

        if (this.nationalityLabel.getBytes(StandardCharsets.UTF_8).length < maxNationalityLabelBytes)
            this.nationalityLabel = this.nationalityLabel + String.join("", Collections.nCopies(
                    maxNationalityLabelBytes - this.nationalityLabel.getBytes(StandardCharsets.UTF_8).length,
                    nullTerminator));

        if (this.thumbnail.getBytes(StandardCharsets.UTF_8).length < maxThumbnailBytes)
            this.thumbnail = this.thumbnail + String.join("", Collections.nCopies(
                    maxThumbnailBytes - this.thumbnail.getBytes(StandardCharsets.UTF_8).length, nullTerminator));

        if (this.description.getBytes(StandardCharsets.UTF_8).length < maxDescriptionBytes)
            this.description = this.description + String.join("", Collections.nCopies(
                    maxDescriptionBytes - this.description.getBytes(StandardCharsets.UTF_8).length, nullTerminator));


        // Combine Attributes into byte array
        try {
            recordBytes.write(ByteBuffer.allocate(Long.BYTES).putLong(this.birthDate.toEpochDay()).array());
            recordBytes.write(ByteBuffer.allocate(Long.BYTES).putLong(this.deathDate.toEpochDay()).array());
            recordBytes.write(ByteBuffer.allocate(Integer.BYTES).putInt(this.wikiPageID).array());
            recordBytes.write(this.personName.getBytes(StandardCharsets.UTF_8));
            recordBytes.write(this.birthPlaceLabel.getBytes(StandardCharsets.UTF_8));
            recordBytes.write(this.fieldLabel.getBytes(StandardCharsets.UTF_8));
            recordBytes.write(this.genreLabel.getBytes(StandardCharsets.UTF_8));
            recordBytes.write(this.instrumentLabel.getBytes(StandardCharsets.UTF_8));
            recordBytes.write(this.nationalityLabel.getBytes(StandardCharsets.UTF_8));
            recordBytes.write(this.thumbnail.getBytes(StandardCharsets.UTF_8));
            recordBytes.write(this.description.getBytes(StandardCharsets.UTF_8));
        } catch (IOException e) {
            e.printStackTrace();
        }

        return recordBytes.toByteArray();
    }

    public byte[] getBytes() {
        return recordBytes;
    }

    @Override
    public String toString() {
        return "Record{" +
               "birthDate=" + birthDate +
               ", deathDate=" + deathDate +
               ", wikiPageID=" + wikiPageID +
               ", personName='" + personName + '\'' +
               ", birthPlaceLabel='" + birthPlaceLabel + '\'' +
               ", fieldLabel='" + fieldLabel + '\'' +
               ", genreLabel='" + genreLabel + '\'' +
               ", instrumentLabel='" + instrumentLabel + '\'' +
               ", nationalityLabel='" + nationalityLabel + '\'' +
               ", thumbnail='" + thumbnail + '\'' +
               ", description='" + description + '\'' +
               '}';
    }
}
