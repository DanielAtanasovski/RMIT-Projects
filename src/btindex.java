import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.time.LocalDate;
import java.util.Arrays;

public class btindex {

    public static void main(String[] args) {
        int    treePageSize       = 4096;
        int    recordLength   = Record.getMaxBytes();
        String nullTerminator = "\u0000";

        // Arguments validation
        if (args.length != 3) {
            System.out.println("Invalid Arguments!");
            return;
        }

//        System.out.print(args[0]);

        if (!args[0].equalsIgnoreCase("-p")) {
            System.out.println("Missing pagesize parameter!");
            return;
        }

        try {
            treePageSize = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.out.println("Unknown pagesize!");
        }

        // Create Tree
        BPTree tree = new BPTree(treePageSize);

        // File Validation
        FileInputStream heapFile = null;
        try {
            heapFile = new FileInputStream(args[2]);
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found!");
            return;
        }

        // Get Pagesize
        String[] heapFileSplit = args[2].split("\\.");
        int heapPageSize = Integer.parseInt(heapFileSplit[1]);

        // Read File
        byte[] pageBytes      = new byte[heapPageSize];
        int    bytesRead      = 0;
        int    records        = 0;
        int    recordsNotIncludingNull = 0;
        int    recordsMatched = 0;
        long   startTime      = System.nanoTime();

        try {
            while ((bytesRead = heapFile.read(pageBytes)) != -1) {

                int recordBytesRead = 0;
                while ((recordBytesRead + Record.getMaxBytes()) <= heapPageSize) {
                    byte[]
                            recordBytes =
                            Arrays.copyOfRange(pageBytes, recordBytesRead, recordBytesRead + Record.getMaxBytes());
                    recordBytesRead += Record.getMaxBytes();

                    long value = (long) records;
                    records += 1;

                    // Add Record to tree
                    Record currentRecord = new Record(recordBytes);

                    // Remove if NULL (LocalDate.MAX == NULL)
                    if (currentRecord.getBirthDate() == LocalDate.MAX)
                        continue;

                    recordsNotIncludingNull += 1;

                    long key = currentRecord.getBirthDate().toEpochDay();


                    tree.insert(key, value);
                }
            }

        } catch (IOException e) {
            System.out.println("Failed to read Heap File");
            return;
        }

        System.out.println("Records Indexed: " + recordsNotIncludingNull);
//        System.out.println("Tree Diagram: ");
//        tree.printTree();

    }

}
