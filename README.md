
# Version 0.1 is only a beta and not ready for use.

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/logo.png?raw=true)

This project contains the source code for the R version of the Genetic Code Analysis Toolkit (GCAT) project. Please refer to the [public homepage](http://www.gcat.bio/) and the [project homepage](http://www.mbi.hs-mannheim.de/research/mathematics-of-the-genetic-information.html) for more information.

# Installation
GCATR is available for R version 3.5 and higher. It requires a C++11 (or later) compiler and [Rcpp (>= 0.12.18)](https://cran.r-project.org/web/packages/Rcpp/index.html) installed on your machine. 
Furthermore the current version of devtools needs to be installed on your computer. Install the R package by:
<br/>starting the a R console and run:
```R
install.packages("devtools")
devtools::install_github("StarmanMartin/GCATR")
```

 
# Components


## Codes

### get_rna_codon_list

This function generates a List of all trinucleotide RNA codon. It will generate the following list:<br/>
_UUU UCU UAU UGU UUC UCC UAC UGC UUA UCA UAA UGA UUG UCG UAG UGG CUU CCU CAU CGU CUC CCC CAC CGC CUA CCA CAA CGA CUG CCG CAG CGG
AUU ACU AAU AGU AUC ACC AAC AGC AUA ACA AAA AGA AUG ACG AAG AGG GUU GCU GAU GGU GUC GCC GAC GGC GUA GCA GAA GGA GUG GCG GAG GGG_
#### Return:
A vector object with all RNA codons
```R
get_rna_codon_list <- function()
# examples
res <- get_rna_codon_list()
```
   
### get_rna_codon_table

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)<br/><br/>
Returns the tables displayed in the fig. above. The tables will be stored in a matrix object. 

#### Return:
A matrix object with all RNA codons

```R
get_rna_codon_table <- function()
# examples
res <- get_rna_codon_table()
```
   
## Graph tools

### code_factor_graph
Prepares a R [igraph](http://igraph.org/r/) object. The graph G(X) is called the representing graph of X or the graph associated to X.
Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*
#### Parameters:
*code* &rarr; [string vector] The DNA or RNA code as list represented by the graph.<br/>
*show_circles* &rarr; [bool] If true the all edges building a circle are colored red.<br/>
*show_longest_path* &rarr; [bool] If true the all edges part of the longest path are colored blue.
#### Return:
A [igraph](http://igraph.org/r/) object
   ```R
      code_factor_graph <- function(code, show_circles=FALSE, show_longest_path=FALSE)
      # example:
      plot(code_factor_graph(c("ACG", "CGA")))
   ```
### code_factor_c3graph
Prepares a R [igraph](http://igraph.org/r/) object. 
Extents the Graph G(X) from _code_factor_graph_ by the so called C3 edges.
If the graph shows a cycle with alternating edges of the C3 edges and the usual edges follows that
the circular permutation of the code is not a circular code. Only works for word length of 3.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*
#### Parameters:
*code* &rarr; [string vector] The DNA or RNA code as list represented by the graph.  
#### Return:
A [igraph](http://igraph.org/r/) object
   ```R
      code_factor_c3graph <- function(code)
      # example:
      plot(code_factor_c3graph(c("ACG", "CGA")))
   ```
### code_factor_circles
Prepares a R [igraph](http://igraph.org/r/) object. Returns only the circles in
G(X) if existing.
#### Parameters:
*code* &rarr; [string vector] The DNA or RNA code as list represented by the graph. 
#### Return:
A [igraph](http://igraph.org/r/) object
  ```R
      code_factor_circles <- function(code)
      # example:
      plot(code_factor_circles(c("ACG", "CGA")))
   ```
### code_factor_longest_path
Prepares a R [igraph](http://igraph.org/r/) object. Returns only the longest Path in
G(X) if existing.
#### Parameters:
*code* &rarr; [string vector] The DNA or RNA code as list represented by the graph. 
#### Return:
A [igraph](http://igraph.org/r/) object
  ```R
      code_factor_longest_path <- function(code)
      # example:
      plot(code_factor_longest_path(c("ACG", "CGT")))
   ```
### seq_factor_graph
Prepares a R [igraph](http://igraph.org/r/) object. The graph G(X) is called the representing graph of X or the graph associated to X.
Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*
#### Parameters:
*seq* &rarr; [string] A DNA or RNA sequence used to extract the code represented by the graph.<br/>
*word_length* &rarr; [unsigned int] The length of the words in the sequence.<br/>
*show_circles* &rarr; [bool] If true the all edges building a circle are colored red.<br/>
*show_longest_path* &rarr; [bool] If true the all edges part of the longest path are colored blue.
#### Return:
A [igraph](http://igraph.org/r/) object
   ```R
      seq_factor_graph <- function(seq, word_length=3, show_circles=FALSE, show_longest_path=FALSE)
      # example:
      plot(seq_factor_graph("ACGCGA", 3))
   ```
### seq_factor_c3graph
Prepares a R [igraph](http://igraph.org/r/) object. 
Extents the Graph G(X) from _seq_factor_graph_ by the so called C3 edges.
If the graph shows a cycle with alternating edges of the C3 edges and the usual edges follows that
the circular permutation of the code is not a circular code. Only works for word length of 3.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*
#### Parameters:
*seq* &rarr; [string] A DNA or RNA sequence used to extract the code represented by the graph. 
#### Return:
A [igraph](http://igraph.org/r/) object 
   ```R
      seq_factor_c3graph <- function(seq)
      # example:
      plot(seq_factor_c3graph("ACGCGA"))
   ```
### seq_factor_circles
Prepares a R [igraph](http://igraph.org/r/) object. Returns only the circles in
G(X) if existing.
#### Parameters:
*seq* &rarr; [string] A DNA or RNA sequence used to extract the code represented by the graph.<br/>
*word_length* &rarr; [unsigned int] The length of the words in the sequence.
#### Return:
A [igraph](http://igraph.org/r/) object
   ```R
      seq_factor_circles <- function(seq, word_length=3)
      # example:
      plot(seq_factor_circles("ACGCGA", 3))
   ```
### seq_factor_longest_path
Prepares a R [igraph](http://igraph.org/r/) object. Returns only the longest Path in
G(X) if existing.
#### Parameters:
*seq* &rarr; [string] A DNA or RNA sequence used to extract the code represented by the graph.<br/>
*word_length* &rarr; [unsigned int] The length of the words in the sequence.
#### Return:
A [igraph](http://igraph.org/r/) object
   ```R
      seq_factor_longest_path <- function(seq, word_length=3)
      # example:
      plot(seq_factor_longest_path("ACGCGT", 3))
   ```

## BDA

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/bda_procedure.png?raw=true)<br/><br/>

### start_bda
To generate a BDA based binary representation of a code or a sequence of codons, you need to start a BDA procedure first.
This function starts a BDA procedure for all trinucleotide RNA codes. After the procedure has been started you need to add BDAs. To add a BDA simply Call *add_bda*. To execute the BDAs call *run_bda_as_matrix* or *run_bda*.<br/>
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:read:<br/>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*
#### Return:
A boolean value. True if the procedure has started correctly.
   ```R
      start_bda <- function()
      # example:
      start_bda()
      add_bda(1, 2, "C", "G", "A", "U")
      add_bda(1, 3, "A", "G", "C", "U")
      res <- run_bda_as_matrix()
   ```
   
### code_start_bda
To generate a BDA based binary representation of a code or a sequence of codons, you need to start a BDA procedure first.
This function starts a BDA procedure for a code vector. After the procedure has been started you need to add BDAs. To add a BDA simply Call *add_bda*. To execute the BDAs call *run_bda*.
*run_bda_as_matrix* only works if the procedure has been started by the *start_bda* function<br/>
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:read:<br/>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*
#### Parameters:
*code* &rarr; [string vector] A DNA or RNA code as list. 
#### Return:
A boolean value. True if the procedure has started correctly.
   ```R
      code_start_bda <- function(code)
      # example:
      code_start_bda(c("ACG", "CAG"))
      add_bda(1, 2, "C", "G", "A", "U")
      add_bda(1, 3, "A", "G", "C", "U")
      res <- run_bda()
   ```
   
### seq_start_bda
To generate a BDA based binary representation of a code or a sequence of codons, you need to start a BDA procedure first.
This function starts a BDA procedure for a RNA or DNA sequence. After the procedure has been started you need to add BDAs. To add a BDA simply Call *add_bda*. To execute the BDAs call *run_bda*.
*run_bda_as_matrix* only works if the procedure has been started by the *start_bda* function<br/>
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:read:<br/>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*
#### Parameters:
*seq* &rarr; [string] A DNA or RNA sequence used to extract the code.<br/>
*word_length* &rarr; [unsigned int] The length of the words in the sequence.
#### Return:
A boolean value. True if the procedure has started correctly.
   ```R
      seq_start_bda <- function(seq, word_length)
      # example:
      seq_start_bda("ACGCAG", 3)
      add_bda(1, 2, "C", "G", "A", "U")
      add_bda(1, 3, "A", "G", "C", "U")
      res <- run_bda()
   ```
   
   
### add_bda
![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/bda_diagramm.png?raw=true)<br/><br/>
To generate a BDA based binary representation of a code or a sequence of codons, you need to start a BDA procedure first.
To do so you can either call *code_start_bda* or *seq_start_bda*. To start a procedure for all RNA codons call *start_bda*. 
After the procedure has been started you can add BDAs. To add a BDA simply Call *add_bda*. 
Each added BDA results one binary digit for each codon. You can add multiple BDAs to one procedure. To execute the BDAs call *run_bda*.
You can also use *run_bda_as_matrix*. Yet, it only works if the procedure has been started by the *start_bda* function<br/>
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:read:<br/>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*
#### Parameters:
*i_1* &rarr; [unsigend int]  A unsigend Integer from 1 - [WORD LENGTH]<br/>
*i_2* &rarr; [unsigend int]  A unsigend Integer from 1 - [WORD LENGTH]<br/>
*Q_11* &rarr; [string]  A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}<br/>
*Q_12* &rarr; [string]  A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}<br/>
*Q_21* &rarr; [string]  A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}<br/>
*Q_22* &rarr; [string]  A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}
#### Return:
A boolean value. True if the BDA is correctly formulated.
   ```R
      add_bda <- function(i_1, i_2, Q_11, Q_12, Q_21, Q_22)
      # example:
      seq_start_bda("ACGCAG", 3)
      add_bda(1, 2, "C", "G", "A", "U")
      add_bda(1, 3, "A", "G", "C", "U")
      res <- run_bda()
   ```
   
### run_bda
This function runs the  BDA procedure and returns the binary representation of the code or a sequence of codons.
A BDA procedure has to be open for this function to be working.
To do so you can either call *code_start_bda* or *seq_start_bda*. To start a procedure for all RNA codons call *start_bda*. 
After the procedure has been started you can add BDAs. To add a BDA simply Call *add_bda*. 
Each added BDA results one binary digit for each codon. You can add multiple BDAs to one procedure. To execute the BDAs call *run_bda*.
You can also use *run_bda_as_matrix*. Yet, it only works if the procedure has been started by the *start_bda* function<br/>
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:read:<br/>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*
#### Return:
A list object with 2 rows. First row the is the code. Second row is the BDA result.
   ```R
      run_bda <- function()
      # example:
      seq_start_bda("ACGCAG", 3)
      add_bda(1, 2, "C", "G", "A", "U")
      add_bda(1, 3, "A", "G", "C", "U")
      res <- run_bda()
   ```

### run_bda_as_matrix
This function runs the  BDA procedure and returns the binary representation of the code or a sequence of codons.
A BDA procedure has to be open for this function to be working. To start a procedure for all RNA codons call *start_bda*. 
After the procedure has been started you can add BDAs. To add a BDA simply Call *add_bda*. 
Each added BDA results one binary digit for each codon. You can add multiple BDAs to one procedure. To execute the BDAs call *run_bda*.
You can also use *run_bda_as_matrix*. Yet, it only works if the procedure has been started by the *start_bda* function<br/>
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:read:<br/>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*
#### Return:
A matrix object with 16 rows. See *run_bda_as_matrix*.
   ```R
      run_bda_as_matrix <- function()
      # example:
      start_bda()
      add_bda(1, 2, "C", "G", "A", "U")
      add_bda(1, 3, "A", "G", "C", "U")
      res <- run_bda_as_matrix()
   ```

## Analysis Tool

### find_amd_analysis_code_in_sequence

Analysis a sequence based on a generic code.

Finds all appearance of a code ion a sequence. Finds the longest connected matches of words of the code in the sequence.
The function also calculates the matching bases of the found words in the sequence.

#### Parameters:
*seq* &rarr; [string] A DNA or RNA sequence.<br/>
*code* &rarr; [string vector] A DNA or RNA code as string vector.

#### Returns
 A List with all analysing results. The list contains following:<br/>
*words*  &rarr;  all found words of the code in the sequence in the correct order.<br/>
*idx_list*  &rarr; the first-letter index of all found words of the code in the sequence in the correct order.<br/>
*rest*  &rarr; all parts of the sequence which are not matching the code.<br/>
*parts*  &rarr; the sequence separated in matching and non matching parts. Odd indexes are matching, even indexes are not matching.<br/>
*longest_match*  &rarr; the longest connected matching sequence.<br/>
*total_match_in_percent*  &rarr; the percentage of the matching parts.

```R
find_amd_analysis_code_in_sequence <- function(seq, code)
# example
code <- c("ACG", "TCG")
seq <- "ACGTCGCGACGTACGACGTCGTACTCGATGCAAGATC"
res <- find_amd_analysis_code_in_sequence(seq, code)
```

### code_check_if_circular
Check if a DNA/RNA code is circular.

This function checks if a genetic code is circular.
Circular codes is an approach for finding the method used in gens for retrieving the correct reading frames.<br/>
For more info on this subject read:<br/>
[ncbi article](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/),<br/>
[2007 Christian MICHEL. CIRCULAR CODES IN GENES](http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf)

#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list.
#### Return:
 Boolean value. True if the code is circular.

```R
code_check_if_circular <- function(code)
# example:
code <- c("ACC", "ACG", "CUU", "GCC", "GGU", "GUU", "UAG", "UAU", "UGC")
if(code_check_if_circular(code)) { ... }
```

### code_check_if_cn_circular
Check if a DNA/RNA code is cn circular.

This function checks if a genetic code is cn circular.
Circular codes is an approach for finding the method used in gens for retrieving the correct reading frames.
For a code to be cn circular means that each circular permutation the codons construct a new circular code.
For more info on this subject read:<br/>
[ncbi article](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/),<br/>
[2007 Christian MICHEL. CIRCULAR CODES IN GENES](http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf)

#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list.
#### Return:
 Boolean value. True if the code is cn circular.

```R
code_check_if_cn_circular <- function(code)
# example:
code <- c("ACC", "ACG", "CUU", "GCC", "GGU", "GUU", "UAG", "UAU", "UGC")
if(code_check_if_cn_circular(code)) { ... }
```

### code_check_if_comma_free
Check if a code is comma free.

The function checks if the code is comma free. 
Comma free is a stronger restricted version of the circular code property.
For more info on this subject read:<br/>
[ncbi article](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/),<br/>
[2007 Christian MICHEL. CIRCULAR CODES IN GENES](http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf)

#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list.
#### Return:
 Boolean value. True if the code comma free.

```R
code_check_if_comma_free <- function(code)
# example:
code <- c("ACC", "AGG", "CGU", "UAA", "UGC")
if(code_check_if_comma_free(code)) { ... }
```

### code_check_if_self_complementary
Check if a code is self complementary.

The function checks if the code is self complementary. A self complementary code contains for 
any codon (word) in the code the corresponding anti-codons.
For more info on this subject read:<br/>
[ncbi article](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/),<br/>
[2007 Christian MICHEL. CIRCULAR CODES IN GENES](http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf)

#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list.
#### Return:
 Boolean value. True if the code self complementary.


```R
code_check_if_self_complementary <- function(code)
# example:
if(code_check_if_self_complementary(c("ACG", "CAG"))) { ... }
```

### code_get_acid
Get acid type of a code

Returns either RNA or DNA depending on the codes Bases. If the code contains only CYTOSINE (C), ADENINE (A), GUANINE (G)
the functions returns DNA. If the code contains THYMINE (T) it will also return DNA. On the other side, if the
the code contains URACIL (U) bases the function returns RNA. If the code contains URACIL (U) & THYMINE (T) or any other letter
then CYTOSINE (C), ADENINE (A), GUANINE (G), URACIL (U) or THYMINE (T) it will return NONE
For more info on this subject read:<br/>
[ncbi article](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/),<br/>
[2007 Christian MICHEL. CIRCULAR CODES IN GENES](http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf)

#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list.
#### Retrun:
 String value. One of NONE, DNA, RNA

```R
code_get_acid <- function(code)
# example:
acid <- code_get_acid(c("ACG", "CAG"))
```

### code_get_one_longest_path_as_vector
Finds one longest path constructable in a code.

Prepares a R path string vector. Extracts all longest paths of the Graph G(X).
If the graph shows a cycle the vector will be empty. Otherwise it returns a vector with one longest path.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*

#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list represented by the graph.

```R
code_get_one_longest_path_as_vector <- function(code)
# example:
l_path <- code_get_one_circle_as_vector(c("ACG", "CGA"))
```

### code_get_all_longest_path_as_vector
Finds all longest path constructable in a code.

Prepares a List of R path string vector. Extracts all longest path of the Graph G(X).
If the graph shows a cycle the list will be empty. Otherwise it returns a list object containing vectors with all
longest paths.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*

@param code A DNA or RNA code as string vector represented by the graph.

```R
code_get_all_longest_path_as_vector <- function(code)
# example:
l_path_list <- code_get_all_longest_path_as_vector(c("ACG", "CGA"))
```

### code_get_one_circle_as_vector
Finds one circle constructable in a code.

Prepares a R path string vector. Extracts all circle path of the Graph G(X).
If the graph shows no cycle the vector will be empty. Otherwise it returns a vector with one
circle paths.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list represented by the graph.

```R
code_get_one_circle_as_vector <- function(code)
# example:
c_path <- code_get_one_circle_as_vector(c("ACG", "CGA"))
```

### code_get_all_circle_as_vector
Finds all circles constructable in a code.

Prepares a List of R path string vector. Extracts all circle path of the Graph G(X).
If the graph shows no cycle the list will be empty. Otherwise it returns a list object containing vectors with all
circle paths.<br/>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*

#### Parameters:
*code*  &rarr; [string vector] A DNA or RNA code as list represented by the graph.

```R
code_get_all_circle_as_vector <- function(code)
# example:
c_path_list <- code_get_all_circle_as_vector(c("ACG", "CGA"))
```

### get_dna_bases
Returns all DNA bases

#### Retrun:
{"T", "C", "A", "G"}

```R
get_dna_bases <- function() 
```
### get_rna_bases
Returns all DNA bases

#### Retrun:
{"U", "C", "A", "G"}
```R
get_rna_bases <- function()
```


# Copyright and license
Code and documentation copyright 2018-2019 Mannheim University of Applied Sciences. Code released under the GPL License, Version 2.0.
