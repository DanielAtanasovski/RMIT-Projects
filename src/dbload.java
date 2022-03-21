/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
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


        System.out.println(records.get(0).toString());
        System.out.println(Arrays.toString(records.get(0).getBytes()));

        try (FileOutputStream fos = new FileOutputStream("test.one")) {
            fos.write(records.get(0).getBytes());
            fos.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }


        System.out.println("Records Loaded: " + records.size());

        System.out.println("TODO: Generate HeapFile");
    }
}
