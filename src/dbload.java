/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class dbload {


    public static void main(String[] args) {
        CSVToRecordConverter csvToRecordConverter = new CSVToRecordConverter();
        List<Record> records = new ArrayList<>();
        try {
            records = csvToRecordConverter.convert("artist.csv");
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Records Loaded: " + records.size());

        System.out.println("TODO: Generate HeapFile");
    }
}
