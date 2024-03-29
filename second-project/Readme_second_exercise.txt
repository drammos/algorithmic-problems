Εργασια 2

Μελη ομαδας:

    - Ιωάννα Οικονόμου 1115201900137
    - Δημήτριος Ράμμος 1125201900161

Σχετικα με τους αλγοριθμους της εργασιας:

    Απο την εργασια εχουμε υλοποιησει τους δυο πρωτους αλγορίθμους, τον local search και τον simulated annealing.
    Η Ιωαννα Οικονόμου ανελαβε να φερει εις περας τον πρωτο αλγοριθμο, Local Search Algorithm.
    Ο Δημήτριος Ράμμος ανελαβε να φερει εις περας τον δευτερο αλγοριθμο, Simulated Annealing Algorithm.
    
    Ο τριτος και τελευταιος αλγοριθμος δεν υλοποιηθηκε καθως η ομαδα μας ειναι δυο(2) ατομων.

Εκκινηση αλγοριθμου:

    Τρεχουμε τους αλγοριθμους μας με την CGAL.5.5.1
    Επομενως αφου εγκαταστησετε την GGAL ακολουθηστε τα παρακατω βηματα:

        - Στα παραδοτέα θα βρειτε ενα αρχειο CMakeLists.txt, χρησιμοποιηστε αυτο για την μεταγλωττιση του
            προγραμματος. Τρέξτε cmake -DCGAL_DIR=/usr/lib/CGAL . για να φτιαχτεί το Makefile.
        
        - Με την παρακατω εντολη θα μεταγλωττισετε τα αρχεια:
            $ make
        
        - Επειτα για να εκκινησετε το προγραμμα τρεξτε την παρακατω εντολη:
            $ ./optimal_polygon -i <input-file> -o <output-file> -algorithm <local_search or simulated_annealing> -L <L parameter according to algorithm>
            –max <maximal area polygonization> –min <minimal area polygonization> –threshold <double> [in local search] –annealing <"local" or "global" or "subdivision" in simulated annealing>

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
                    
                    Optimal Area Polygonization
                    0 0
                    4 0
                    4 4
                    0 0 4 0
                    4 0 4 4
                    4 4 0 0
                    Algorithm: <local_search or simulated_annealing>_[max or min]
                    area_initial <double> [only in local search and simulated annealing]
                    area: <double>
                    ratio_initial <double> [only in local search and simulated annealing]
                    ratio: <double
                    construction time: <milliseconds as integer>
                    
Κατάλογος αρχείων:
    Στο παραδοτέο μπορείτε να βρείτε τα παρακάτω αρχεία:
        -main.cpp ->περιέχει τη συνάρτηση main.
        -incremental.cpp ->περιέχει την υλοποίηση του πρώτου αλγορίθμου της πρώτης εργασίας.
        -incremental.hpp ->περιέχει τις απαραίτητες δηλώσεις για τον πρώτο αλγόριθμο της πρώτης εργασίας.
        -convex_hull_algorithmic.cpp ->περιέχει την υλοποίηση του δεύτερου αλγορίθμου της πρώτης εργασίας.
        -convex_hull_algorithmic.hpp ->περιέχει τις απαραίτητες δηλώσεις για τον δεύτερο αλγόριθμο της πρώτης εργασίας.
        -local_search.cpp ->περιέχει την υλοποίηση του πρώτου αλγορίθμου της δεύτερης εργασίας.
        -local_search.hpp ->περίχει την υλοποίηση του πρώτου αλγορίθμου της δεύτερης εργασίας.
        -simulated_annealing.cpp -> περιέχει την υλοποίηση του πρώτου αλγορίθμου της δεύτερης εργασίας(του Simulated Annealing).
        -simulated_annealing.hpp -> περιέχει την υλοποίηση του πρώτου αλγορίθμου της δεύτερης εργασίας(του Simulated Annealing).
        -subdivision.cpp -> περιέχει την υλοποίηση του πρώτου αλγορίθμου της δεύτερης εργασίας(του Simulated Annealing - Subdivision).
        -subdivision.hpp -> περιέχει την υλοποίηση του πρώτου αλγορίθμου της δεύτερης εργασίας(του Simulated Annealing - Subdivision).
        -CMakeLists.txt ->απαραίτητο αρχείο για τη μετταγλώτιση του προγγράμματος.
        -Το παρόν readme.

Για την main.cpp:

    Διαβαζουμε τα ορισματα απο την γραμμη εντολων επειτα διαβαζουμε το αρχειο εισοδου και αποθηκευουμε 
    τα points σε ενα vector.
    Αν ο αλγοριθμος μας ειναι ο simulated_annealing με ορισμα -annealing subdivision τοτε καλουμε τον subdivision
    χωρις να χουμε καλεσει την συναρτηση setup η οποια καλει εναν αλγοριθμο πρωτα της πρωτη εργασιας και δημιουργει πολυγωνο.

    Σε διαφορετικη περιπτωση τρέχουμε έναν από τους αλγορίθμους της πρώτης εργασίας για να δημιουργηθεί το πολύγωνο 
    και στη συνέχεια αναλογα τον αλγοριθμο επιλογης απο την γραμμη εντολων επιλεγουμε τον αλγοριθμο βελτιστοποίησης
    με τα καταλληλα ορισματα.

Για τον local search algorithm:

    Η υλοποίηση του συγκεκριμένου αλγορίθμου αποτελείται από μια κεντρική συνάρτηση που ονομάζεται local_search και από τις παρακάτω
    επιμέρους συναρτήσεις: 
        -find_paths()->βρίσκει όλα τα πιθανά μονοπάτια του πολυγώνου.
        -remove_path()->αφαιρεί το εκάστοτε μονοπάτι από το υπάρχον πολύγωνο.
        -change_path()->τοποθετεί το εκάστοτε μονοπάτι ανάμεσα στα άκρα μιας συγκεκριμένης ακμής.

    Ο αλγόριθμος δέχεται το πολύγωνο που έχει επιστρέψει κάποιος από τους αλγορίθμους της πρώτης εργασίας και βρίσκει όλα τα πιθανά paths
    μήκους L που υπάρχουν σε αυτό. Στη συνέχεια για κάθε ένα από αυτά τα μονοπάτια ελέγχει σε ποιά άλλη ακμή του πολυγώνου θα μπορούσε
    να μεταφερθεί ετσι ώστε το εμβαδόν να γίνει μέγιστο ή ελάχιστο. 

    Ο έλεγχος αυτός γίνεται με τον εξής τρόπο:

    Αρχικά, το εκάστοτε μονοπαι αφαιρείται από το αρχικό πολύγωνο. 

    Στη συνέχεια, ελέγχεται τι θα συμβει αν μεταφέρουμε αυτό το μονοπάτι ανάμεσα στα άκρα της ακμής που ελέγχεται κάθε φορά.
    Αν το πολύγωνο που προκύπτει είναι κανονικό και το εμβαδόν του μικραίνει ή μεγαλώνει ανάλογα με το τι θέλουμε, τότε το 
    προσθέτουμε στα υποψήφια νέα πολύγωνα.

    Αφού αυτός ο έλεγχος ολοκληρωθεί για κάθε μονοπάτι και για κάθε ακμή του πολυγώνου, τότε κρατάμε το υποψήφιο πολύγωνο που 
    δίνει το μέγιστο ή ελάχιστο εμβαδόν, ανάλογα τις παραμέτρους.


Για τον Simulated Annealing:

Ο αλγοριθμος δεχεται ενα Polygon, ενα L, min_max, annealing, Segment_2, Segment_2:

    - Polygon το πολυγωνο που χει δημιουργηθεί
    - L ενας αριθμος που χρησιμοποιειται για την μειωση της θερμοκρασιας
    - min_max επειδθκνυει αν θα χρησιμοποιειται η min or max energy.
    - annealing ποιο step εκτελειτε
    - Segment_2 ειναι δυο ακμες που μπορει να μην εχουν τιμη δηλαδη nullptr, αν καποια απο αυτες εχει τοτε
        παραβλεπουμε αυτη την ακμη και δεν την "διαχωριζουμε" απο το πολυγωνο σε καμια περιπτωση.
        Αυτο ισχυει για το global step καθως καλειται απο τον subdivision με ορισμα global.

    Η κυρια συναρτηση μας ειναι simulated_annealing().
    Απο κει υπολογιζεται η αρχικη ενεργεια του πολυγωνου καθως και δινεται μια τιμη στην θερμοκρασια.
    Αρχιζουμε μια επαναληψη οσο η θερμοκρασια ειναι θετικος αριθμος.

    Διαλεγουμε αναμεσα στο global and local step αναλογα το αρισμα annealing.
    Για το πολυγωνο που μας επιστεφεται υπολογιζουμε την ενεργεια του και την συγκρινουμε με αυτη του παλιου πολυγωνου
    Αν η λυση νεου πολυγωνου δεν ειναι καλη τοτε αποφασιζουμε με βαση την τυχαιοτητα χρησιμοποιωντας το metropolis_criterion
    Υπαρχει η υλοποίηση του σε συναρτηση  metropolis_criterion().

    Επιστρεφεται ενα πολυγωνο.

    For local-step: 
        Χρησιμοπειται το function local_step() που προσομοιωνει το βημα αυτο του αλγοριθμου.
        Διαλεγει μαι τυχαια Κορυφη  q. Βρισκει την προηγουμενη q_before και επομενες q_next_1, q_next_2.
        Και δοκιμαζει να σπασει την  q - q_before ακμη και την q_next_1 - q_next_2, και να δημιουργησει τις 
        q_before - q_next_1 & q - q_next_2.

        Για τον ελεγχο για do_intersect() φτιαχνει ενα box που ελεγχει ποια σημεια εμπεριεχονται σε αυτο και ελεγχει.
        Αν δεν υπαρχει καποιο προβλημα στο πολυγωνο τοτε το επιστρεφει ως λυση.
    
    For global-step:
        Χρησιμοπειται το function global_step(). Επιλεγει δυο τυχαιες κορυφες p,s.
        Αν p με p_before και p_next προηγουμενη και επομενη κορυφη με ακμες αντιστοιχα και t επομενη της s 
        ακμης με ακμη αντιστοιχα.

        Χωριζουμε το p απο τις δυο ακμες του και ετσι δημιουργειται μια ακμη p_before - p_next και αλλες δυο 
        s - p & p - t.
        
        Ολα αυτα δημιουργουνται αν δεν χαλαει η ενοια του simple πολυγωνου και καποια απο τις ακμες που διαχωριζουμε
        δεν ειναι μια απο τις 2 ακμες που δινονται ως ορισμα(αν δινεται καποια ακμη αλλιως ειναι nullptr).
         Αν δεν υπαρχει καποιο προβλημα στο πολυγωνο τοτε το επιστρεφει ως λυση.

Για τον subdivision:
Ο αλγοριθμος εχει τα ορισματα
    - vector from points
    - L 
    - min_max
    Η κυρια συναρητση μας ειναι η subdivision().
        - Για αρχη ταξινομουμε τα points σε αυξουσα σειρα με βαση το x στον αξονα.
        - Διαλεγουμε εναν τυχαιο αριθμο 10 <= m <= 100.
            Το m καθοριζει ποσα τουλαχιστον θα ειναι τα σημεια για καθε "παρτιδα" σημειων που θα Χωριζουμε.
        - Επειτα προσπαθη να κανει διασπαση ολων των points σε spal.
            Πρεπει καθε spal να εμπεριεχει m points.
            Για αρχη βαζουμε m -1 σημεια μετα για τα σημεια >= m ελεγχουμε αν ισχυει μια συνθηκη.
            Αν ισχυει τοτε κλεινουμε αυτο spal σε αυτο το σημειο και ανοιγουμε καποιο αλλο που συνεχιζει απο κει που σταματησε
            το προηγουμενο αλλιως αν δεν ισχυει η συνθηκη μας τοτε συνεχιζουμε μεχρι να βρουμε ενα σημειο
            που την ικανοποιει.

            Η συνθηκη ειναι οτι για το point που εξεταζω πρεπει να χει αριστερα του για τα σημεια του spal που εξεταζουμε
            - Τουλαχιστον ενα σημειο με χαμηλοτερο y.
            Πρεπει δεξια του για τα υπολοιπα σημεια του αρχικου-ταξινομημενου vector να εχει επισης τουλαχιστον ενα
            με χαμηλοτερο y.

        - Για καθε spal αποθηκευουμε καποιες πληροφοριες οπως δεξιοτερο και αριστερο σημειο και ακμες(θα εξηγησουμε στη συνεχεια) και τα σημεια του.

        - Για καθε spal καλουμε τον  convex_hull που δημιουργει ενα εξωτερικο πολυγωνο με τα σημεια του για δεξιοτερο
        και αριστεροτερο σημειο μαρκαρουμε τις ακμες που δημιουργει το convex_hull και τις αποθηκευουμε ωστε να μην αλλαξουν ποτε 
        και χαθει η ιδιοτητα.

        - Επειτα καλουμε για καθε ενα spal τον αλγοριθμο  convex_hull  της πρωτης εργασιας τον οποιο
        εχουμε τροποποιησει ωστε να μην αλλαζει συγκεκριμενες ακμες του πολυγωνου.
        
        - Αυτος μας επιστρεφει για καθε spal ενα πολυγωνο για το οποιο καλουμε τον simulated_annealing with global_step.

        - Τελος κανουμε merge τα πολυγωνα ενωνοντας τα μεταξυ τους διαχωριζοντας τις ακμες που μακραραμε και ενωνοντας τα μη κοινα σημεια
        μεταξυ τους.




Παρατηρήσεις:

    Παρατηρούμε ότι ο local search είναι αρκετά πιο αργός από τον simulated annealing αλλά δίνει μεγαλύτερες διαφορές εμβαδόντος
    ανάμεσα στο αρχικό και το τελικό πολύγωνο. Επίσης, ο simulated annealing λόγω του metropolis criteria σπάνια δίνει λάθος αποτέλεσμα.

Παραδείγματα εκτελέσεων:

    -./optimal_polygon -i 20.instance -o outfile -algorithm local_search -L 3 -max -threshold 0.3
     Αποτέλεσμα:
     Optimal Area Polygonization
     Algorithm: local_search_-max
     area_initial:3.5095e+07
     area:4.20619e+07
     ratio_initial:0.734856
     ratio:0.880737
     construction time: 681837

    -./optimal_polygon -i 40.instance -o outfile -algorithm local_search -L 3 -max -threshold 0.3
     Αποτέλεσμα:
     Optimal Area Polygonization
     Algorithm: local_search_-max
     area_initial:2.10929e+07
     area:4.47092e+07
     ratio_initial:0.415466
     ratio:0.880637
     construction time: 10605003

    -./optimal_polygon -i 60.instance -o outfile -algorithm local_search -L 3 -min -threshold 0.3
     Αποτέλεσμα:
     Optimal Area Polygonization
     Algorithm: local_search_-min
     area_initial:1.52662e+11
     area:4.80977e+10
     ratio_initial:0.585869
     ratio:0.184584
     construction time: 42271987

    -./optimal_polygon -i 100.instance -o outfile -algorithm local_search -L 3 -min -threshold 0.3
     Αποτέλεσμα:
     Optimal Area Polygonization
     Algorithm: local_search_-min
     area_initial:4.06317e+07
     area:1.22302e+07
     ratio_initial:0.538291
     ratio:0.162026
     construction time: 409404354

    -./optimal_polygon -i 100.instance -o outfile -algorithm simulated_annealing -L 1000 -min -annealing local
     Αποτελέσματα:
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-min
     area_initial:3.84998e+07
     area:3.63328e+07
     ratio_initial:0.510048
     ratio:0.481339
     construction time: 11400450

    -./optimal_polygon -i 200.instance -o outfile -algorithm simulated_annealing -L 1000 -min -annealing local
     Αποτελέσματα:
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-min
     area_initial:1.3558e+08
     area:1.35019e+08
     ratio_initial:0.498187
     ratio:0.496127
     construction time: 12320540

    -./optimal_polygon -i 1000.instance -o outfile -algorithm simulated_annealing -L 1000 -min -annealing local
     Αποτελέσματα:
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-min
     area_initial:3.871e+07
     area:3.81326e+07
     ratio_initial:0.448869
     ratio:0.442174
     construction time: 127314189

    -./optimal_polygon -i 20.instance -o outfile -algorithm simulated_annealing -L 1000 -min -annealing global
     Αποτελέσματα:
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-min
     area_initial:2.9613e+07
     area:2.31853e+07
     ratio_initial:0.620068
     ratio:0.485478
     construction time: 864117

    -./optimal_polygon -i 40.instance -o outfile -algorithm simulated_annealing -L 1000 -min -annealing global
     Αποτελέσματα:
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-min
     area_initial:2.55988e+07
     area:2.55988e+07
     ratio_initial:0.504218
     ratio:0.504218
     construction time: 1638989

    -./optimal_polygon -i 100.instance -o outfile -algorithm simulated_annealing -L 1000 -min -annealing global
     Αποτελέσματα:
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-min
     area_initial:4.06416e+07
     area:3.98421e+07
     ratio_initial:0.538422
     ratio:0.527831
     construction time: 15546657

    -./optimal_polygon -i 200.instance -o outfile -algorithm simulated_annealing -L 1000 -max -annealing global
     Αποτελέσματα:
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-max
     area_initial:1.38003e+08
     area:1.4745e+08
     ratio_initial:0.507089
     ratio:0.541801
     construction time: 42869270

    ./optimal_polygon -i 1000.instance -o outfile -algorithm simulated_annealing -L 1000 -min -annealing subdivision
     Optimal Area Polygonization
     Algorithm: simulated_annealing_-min
     area:-3.78429e+07
     ratio:-0.438815
     construction time: 32930229