Εργασια 1

Μελη ομαδας:

    - Ιωάννα Οικονόμου 1115201900137
    - Δημήτριος Ράμμος 1125201900161

Σχετικα με τους αλγοριθμους της εργασιας:

    Απο την εργασια εχουμε υλοποιησει τους δυο πρωτους αλγορίθμους, τον incremental και τον convex hull.
    Η Ιωαννα Οικονόμου ανελαβε να φερει εις περας τον πρωτο αλγοριθμο, Incremental Algorithm.
    Ο Δημήτριος Ράμμος ανελαβε να φερει εις περας τον δευτερο αλγοριθμο, Convex Hull Algorithm.
    
    Ο τριτος και τελευταιος αλγοριθμος δεν υλοποιηθηκε καθως η ομαδα μας ειναι δυο(2) ατομων και δεν ηταν απαραιτητoς
    να υλοποιηθει για την ομαδα μας.

Εκκινηση αλγοριθμου:

    Τρεχουμε τους αλγοριθμους μας με την CGAL.5.5.1
    Επομενως αφου εγκαταστησετε την GGAL ακολουθηστε τα παρακατω βηματα:

        - Στα παραδοτέα θα βρειτε ενα αρχειο CMakeLists.txt, χρησιμοποιηστε αυτο για την μεταγλωττιση του
            προγραμματος. Τρέξτε cmake -DCGAL_DIR=/usr/lib/CGAL . για να φτιαχτεί το Makefile.
        
        - Με την παρακατω εντολη θα μεταγλωττισετε τα αρχεια:
            $ make
        
        - Επειτα για να εκκινησετε το προγραμμα τρεξτε την παρακατω εντολη:
            $ ./main -i <input-file> -o <output-file> -algorithm <incremental or convex_hull> -edge_selection <1 or 2 or 3> -initialization <1a or 1b or 2a or 2b>

                - Οπου, <input-file> το αρχειο εισοδου που ακολουθα την παρακατω μορφη:

                    # <γραμμή περιγραφής σημειοσυνόλου>
                    # parameters "convex_hull": {"area": "Χ"} // όπου Χ η επιφάνεια του ΚΠ2
                    0 x0 y0
                    1 x1 y1
                    … … …
                    n-1 xn yn

                    όπου n είναι το πλήθος των σημείων του σημειοσυνόλου και xi, yi οι συντεταγμένες (θετικοί ακέραιοι).

                - Οπου, <output-file>  το αρχειο για την εκτυπωση αποτελεσματων.
                    Για παραδειγμα εχει την μορφη:
                    
                    Polygonization
                    0 0
                    4 0
                    4 4
                    0 0 4 0
                    4 0 4 4
                    4 4 0 0
                    Algorithm: <incremental or convex_hull>_edge_selection<1 or 2 or 3
                    where applicable>_initialization<incremental and onion options accordingly>
                    area: 8
                    ratio: 1
                    construction time: <milliseconds as integer>

                - Οπου, <incremental or convex_hull> η επιλογη αλγοριθμου

                - Οπου, -edge_selection <1 or 2 or 3> επιλογη ορατης ακμης δηλαδη,

                    1 -> Τυχαία επιλογή ορατής ακμής
                    2 -> Επιλογή ορατής ακμής έτσι ώστε να προστίθεται ελάχιστο εμβαδό
                    3 -> Επιλογή ορατής ακμής έτσι ώστε να προστίθεται μέγιστο εμβαδό.

                - Οπου, -initialization <1a or 1b or 2a or 2b> αφορα τον αυξητικο αλγοριθμο.
                    
                    1a -> Ταξινόμηση ως προς x φθίνουσα.
                    1b -> Ταξινόμηση ως προς x αυξουσα.
                    2a -> Ταξινόμηση ως προς y φθίνουσα.
                    2b -> Ταξινόμηση ως προς y αυξουσα.
                    
Κατάλογος αρχείων:
    Στο παραδοτέο μπορείτε να βρείτε τα παρακάτω αρχεία:
        -main.cpp ->περιέχει τη συνάρτηση main.
        -incremental.cpp ->περιέχει την υλοποίηση του πρώτου αλγορίθμου.
        -incremental.hpp ->περιέχει τις απαραίτητες δηλώσεις για τον πρώτο αλγόριθμο.
        -convex_hull_algorithmic.cpp ->περιέχει την υλοποίηση του δεύτερου αλγορίθμου.
        -convex_hull_algorithmic.hpp ->περιέχει τις απαραίτητες δηλώσεις για τον δεύτερο αλγόριθμο.
        -CMakeLists.txt ->απαραίτητο αρχείο για τη μετταγλώτιση του προγγράμματος.
        -Το παρόν readme.
        -Φάκελος .git.
    
Για την main.cpp:

    Διαβαζουμε τα ορισματα απο την γραμμηε εντολων επειτα διαβαζουμε το αρχειο εισοδου και αποθηκευουμε 
    τα points σε ενα vector και επειτα αναλογα τον αλγοριθμο επιλογης απο την γραμμη εντολων επιλεγουμε τον
    αλγοριθμο εκτελεσης με τα καταλληλα ορισματα.

Για τον Incremental Algorithm:
    Η υλοποίηση του συγκεκριμένου αλγορίθμου αποτελείται από μια κεντρική συνάρτηση που ονομάζεται incremental και από τις παρακάτω επιμέρους         
    συναρτήσεις: 
        -compare_1a, compare_1b, compare_2a, compare_2b ->compare συναρτήσεις για το sorting ανάλογα την τιμή του initialization.
        -sorting ->ταξινόμηση σημείων.
        -orientation ->συντονίζει τον προσανατολισμό του ΚΠ και του πολυγόνου.
        -red_edges ->βρίσκει τις κόκκινες ακμές.
        -visible_edges ->βρίσκει τις ορατές ακμές για μια κόκκινη ακμή.
        -random_selection, minimum_area, maximum_area ->συναρτήσεις επιλογής ορατής ακμής ανάλογα με την τιμή του edge_selection.
        
    Παρατηρήσεις όσον αφορά την υλοποίηση του αλγορίθμου:
        -Για τον υπολογισμό των κόκκινων ακμώ χρησιμοποιείται η διαφορά του ΚΠ πριν προστεθεί το νέο σημείο με το ΚΠ αφού προστεθεί το νέο σημείο, δηλαδή 
        κόκκινες ακμές είναι αυτές που περιλαμβάνονται στο πρώτο ΚΠ αλλά όχι στο δεύτερο.
        -Όσον αφορά τις ορατές ακμές αρχικά γίνεται ένας έλγχος για το αν η κοκκινη ακμή για την οποία εξετάζουμε τις ορατές είναι κομμάτι ης πολυγωνικής 
        γραμμής ή όχι. Αν είναι τότε γίνεται έλεγχος για το αν το νέο σημείο που πρόκειται να προστεθεί είναι συνευθειακό με κάποιο από τα άκρα της  
        κόκκινης ακμής. Αν είναι, η ακμή δεν είναι ορατή, αλλιώς είναι.
         
        Αν πάλι η κόκκινη ακμή δεν είναι μέρος της πολυγωνικής γραμμής, πρέπει να βρούμε την αλυσίδα του πολυγώνου που βρίσκεται πίσω από την κόκκινη    
        ακμή. Ξεκινάμε ψάχνοντας την ακμή του πολυγώνου που έχει για πρώτο σημείο το πρώτο σημείο της κόκκινης ακμής και συνεχίζουμε το iteration μέχρι 
        να βρούμε ακμή του πολυγώνου που έχει σαν δεύτερο σημείο το δεύτερο σημείο της κόκκινης ακμής. Για κάθε μία από τις ακμές του πολυγώνου που     
        βρίσκονται ενδιάμεσα ελέγχουμε αν τα ευθύγραμμα τμήματα που ενώνουν το νέο σημείο με τα άκρα αυτής της ακμής, τέμνουν οποιαδήποτε άλλη ακμή του
        πολυγώνου (εκτός φυσικά από αυτές που βρίσκονται πριν και μετά με τις οποίες έτσι κι αλλιώς τέμνονται προφανώς). Επίσης ελέγχουμε αν το         
        ευθύγραμμο τμήμα που ενώνει το νέο σημείο με το μέσο της ακμής που ελέγχουμε, τέμνει οποιαδήποτε ακμή του πολυγώνου. Αν περαστούν αυτά τα τεστ
        επιτυχώς, η ακμή είναι ορατή, αλλιώς απορρίπτεται.
        -Η συνάρτηση incremental επιστρέφει στη main το εμβαδόν του πολυγώνου που δημιούργησε.
        
Για τον Convex Hull Algorithm:

    Ο αλγοριθμος ειναι υλοποιημενος στο convex_hull_algorithmic.cpp με το αντιστοιχο αρχειο κεφαλιδας convex_hull_algorithmic.hpp.
    Η κυρια συναρτηση ειναι η convex_hull που καλειται απο το main-program(main.cpp).
    Η συναρτηση convex_hull δημιουργει το ΚΠ και το αρχικο πολυγονο και επειτα αναλογα με το edge_selection
    επιλεγει ποιον αλγοριθμο θα εκετελεσει αναλογα με το ορισμα εισοδου.
    
    Η συναρτηση random_edge αναφερεται στην περιπτωση που edge_selection = 1, και επιλεγει τυχαια ακμη για την οποια
        μπορει να υπαρχει ορατο εσωτερικο σημειο και επιλεγει το κοντινοτερο

    Η συναρτηση min_area αναφερεται στην περιπτωση που edge_selection = 2, και επιλεγει το τριγωνο εκεινο για το οποιο
        το εμβαδον ελαχιστοποιειται μεταξυ της ακμης και του κοντινοτερου εσωτερικου σημειου που επιλεκτηκε.

    Η συναρτηση max_area αναφερεται στην περιπτωση που edge_selection = 3, και επιλεγει το τριγωνο εκεινο για το οποιο
        το εμβαδον μεγιστοποιηται της ακμης και του κοντινοτερου εσωτερικου σημειου που επιλεκτηκε.

    Στο convex_hull επιστρεφεται το polygon για το οποιο υπολογιζεται το εμβαδον του, το οποιο επιστρεφεται στο main-function.
    
Παραδείγματα εκτελέσεων:

    -./main -i euro-night-0000100.instance -o output -algorithm convex_hull -edge_selection 3
    Αποτέλεσμα:
    ratio: 0.244309
    area: 1.84411e+07
    construction time: 95405
    
    -./main -i euro-night-0000100.instance -o output -algorithm incremental -edge_selection 3 -initialization 1a
    Αποτέλεσμα:
    ratio: 0.766575
    area: 5.78632e+07
    construction time: 20683
    
    -./main -i euro-night-0001000.instance -o output -algorithm convex_hull -edge_selection 3
    Αποτέλεσμα:
    ratio: 0.190247
    area: 1.64067e+07
    construction time: 563850463
    
    -./main -i euro-night-0005000.instance -o output -algorithm incremental -edge_selection 3 -initialization 1a
    Αποτέλεσμα:
    ratio: -0.180341
    area: -6.34659e+07
    construction time: 9873322
    (Το εμβαδόν σε αυτή την περίπτωση δεν χωράει σε long double)
    
    -./main -i euro-night-0001000.instance -o output -algorithm incremental -edge_selection 1 -initialization 1a
    Αποτέλεσμα:
    ratio: 0.45091
    area: 3.8886e+07
    construction time: 333222
    
    -./main -i paris-0000500.instance -o output -algorithm incremental -edge_selection 1 -initialization 1a
    Αποτέλεσμα:
    ratio: 0.695149
    area: 2.06872e+08
    construction time: 823826
    
    -./main -i paris-0000500.instance -o output -algorithm convex_hull -edge_selection 1
    Αποτελέσματα:
    ratio: 0.479216
    area: 1.42612e+08
    construction time: 494136
    
    
    
    Τα αρχεία που δοκιμάζονται παραπάνω είναι αναρτημένα στο eclass του μαθήματος.
