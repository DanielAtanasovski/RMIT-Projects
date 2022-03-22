/*
 * Copyright (c) 2022. Daniel Atanasovski.
 */

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class dbload {
    public static void main(String[] args) {
        CSVToRecordConverter csvToRecordConverter = new CSVToRecordConverter();

        int pageSize = 4096;
        String fileName = "artist.csv";

        if (args.length == 3) {
            // full args
            if (args[0].equalsIgnoreCase("-p")) {
                pageSize = Integer.parseInt(args[1]);
                fileName = args[2];
            } else {
                System.out.println("MALFORMED ARGUMENTS!");
                return;
            }
        } else if (args.length == 1) {
            // Provided datafile only
            fileName = args[0];
        } else {
            System.out.println("NO ARGUMENTS PROVIDED!");
            return;
        }

        List<Record> records = new ArrayList<>();
        try {
            records = csvToRecordConverter.convert(fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }


//        System.out.println(records.get(0).toString());
//        System.out.println(Arrays.toString(records.get(0).getBytes()));

        try (FileOutputStream fos = new FileOutputStream("test.one")) {
            fos.write(records.get(0).getBytes());

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }


        System.out.println("Records Loaded: " + records.size());

        System.out.println("TODO: Generate HeapFile");
    }
}
