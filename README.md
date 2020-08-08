#  Genetic Code Analysis Toolkit (GCAT) in R -> GCATR
## Version 0.1 is only a beta and not ready for use.

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/logo.png?raw=true)

This project contains the source code for the R version of the Genetic Code Analysis Toolkit (GCAT) project. Please refer to the [cammbio homepage](https://www.cammbio.hs-mannheim.de/institute.html) for more information.

# Installation
GCATR is available for R version 3.5 and higher. It requires a C++11 (or later) compiler and [Rcpp (>= 0.12.18)](https://cran.r-project.org/web/packages/Rcpp/index.html) installed on your machine. 
Furthermore the current version of devtools has to be installed on your computer. If you are using Microsoft Windows, then you need to install [Rtools](https://cran.r-project.org/bin/windows/Rtools/)

Starting a new R console and run:
```R
install.packages("devtools")
devtools::install_github("StarmanMartin/GCATR")
```

 
# Function outline

<!--outline-start-->
### [General code tools](#general-circular-codes)

[code_as_unique_vector](#code_as_unique_vector)<br>
[code_as_vector](#code_as_vector)<br>
[code_block_length](#code_block_length)<br>
[code_transform_tuples](#code_transform_tuples)<br>
[shift_tuples](#shift_tuples)<br>

### [General circular code tools](#general-circular-codes)

[generate_code_by_min_value](#generate_code_by_min_value)<br>

[code_check_if_circular](#code_check_if_circular)<br>
[code_check_if_cn_circular](#code_check_if_cn_circular)<br>
[code_check_if_code](#code_check_if_code)<br>
[code_check_if_comma_free](#code_check_if_comma_free)<br>
[code_check_if_k_circular](#code_check_if_k_circular)<br>
[code_k_value](#code_k_value)<br>

[seq_get_tuple_count](#seq_get_tuple_count)<br>
[seq_get_info](#seq_get_info)<br>
[find_and_analysis_code_in_sequence](#find_and_analysis_code_in_sequence)<br>

### [Graph based functions](#graph-based-functions)

[code_factor_cycle](#code_factor_cycle)<br>
[code_factor_graph](#code_factor_graph)<br>
[code_factor_longest_path](#code_factor_longest_path)<br>

[code_get_one_cycles_as_vector](#code_get_one_cycles_as_vector)<br>
[code_get_one_longest_path_as_vector](#code_get_one_longest_path_as_vector)<br>
[code_get_all_cycles_as_vector](#code_get_all_cycles_as_vector)<br>
[code_get_all_longest_path_as_vector](#code_get_all_longest_path_as_vector)<br>
[code_path_end_vertices_miner](#code_path_end_vertices_miner)<br>

### [Genetic circular codes tools](#generic-circular-codes)

[genetic_codes_as_df_by_index](#genetic_codes_as_df_by_index)<br>
[genetic_codes_by_index](#genetic_codes_by_index)<br>
[genetic_codes_by_name](#genetic_codes_by_name)<br>
[print_all_translation_tables](#print_all_translation_tables)<br>

[code_strip_complements](#code_strip_complements)<br>
[code_check_if_self_complementary](#code_check_if_self_complementary)<br>
[code_get_acid](#code_get_acid)<br>
[code_is_translatable](#code_is_translatable)<br>

[code_get_all_amino_acids](#code_get_all_amino_acids)<br>
[code_get_amino_acids](#code_get_amino_acids)<br>

[code_named_transform_tuples](#code_named_transform_tuples)<br>

[codons_to_tessera](#codons_to_tessera)<br>
[code_check_if_tessera](#code_check_if_tessera)<br>

[get_rna_bases](#get_rna_bases)<br>
[get_rna_codon_list](#get_rna_codon_list)<br>
[get_rna_codon_table](#get_rna_codon_table)<br><!--accessory:[![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)]-->

[get_dna_bases](#get_dna_bases)<br>
[get_dna_codon_list](#get_dna_codon_list)<br>
[get_dna_codon_table](#get_dna_codon_table)<br>

[code_pdf_report](#code_pdf_report)<br>


### [Conductance](#conductance)

[get_average_conductance_of_code](#get_average_conductance_of_code)<br>
[get_average_conductance_of_codeidx](#get_average_conductance_of_codeidx)<br>
[get_max_conductance_of_code](#get_max_conductance_of_code)<br>
[get_max_conductance_of_codeidx](#get_max_conductance_of_codeidx)<br>
[get_min_conductance_of_code](#get_min_conductance_of_code)<br>
[get_min_conductance_of_codeidx](#get_min_conductance_of_codeidx)<br>



### [Binary Dichotomic Algorithm (BDA)](#binary_dichotomic_algorithm_(BDA))

[BDATools](#BDATools)<br><!--accessory:[![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)]-->
[start_bda](#start_bda)<<br>
[code_start_bda](#code_start_bda)<br>
[add_rule](#add_rule)<br><!--accessory:[![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/bda_diagramm.png?raw=true)]-->
[run_bda](#run_bda)<br>
[run_bda_as_matrix](#run_bda_as_matrix)<br>

<!--outline-end-->

<!--doc-start-->
## General code tools

### code_as_unique_vector

#### Usage
```R 
code_as_unique_vector(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
StringVector code as vector.


#### Description
 
Turns a sequence or a single string code into a code (ordered string set).


#### Examples
```R 
code_vec <- code_as_unique_vector("CAGACGACG", 3)
code_vec <- code_as_unique_vector("CAG ACG ACG")

```
<hr>

### code_as_vector

#### Usage
```R 
code_as_vector(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
StringVector code as vector.


#### Description
 
Turns a sequence or a single string code into a string vector.


#### Examples
```R 
code_vec <- code_as_vector("ACGCAG", 3)
code_vec <- code_as_vector("ACG CAG")

```
<hr>

### code_block_length

#### Usage
```R 
code_block_length(code)
```

#### Arguments
 
*code*	is either a string vector or a string. It has to be a set of words/blocks<br>


#### Return
 
block length


#### Description
 
This function gets the block length of a code.


#### Examples
```R 
block.length <- code_block_length(c("ACG", "GAT"))
block.length <- code_block_length("ACG GAT")

```
<hr>

### code_transform_tuples

#### Usage
```R 
code_transform_tuples(from, to, code, tuple_length = -55555L)
```

#### Arguments
 
*from*	the origin letters which are maped to the letters of the *to* parameter.<br>

*to*	the transformation target letters which are maped letters of to the *from* parameter.<br>

*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
transformed code as String vector


#### Description
 
This function transforms all tuples in code. The single letters get transformed by the rules which are set as parameter.
The rules are defined as two strings, the *from* and the *to* parameter. These two parameters have to be
strings of the same length. Each letter in the *from* string gets transformed to the corresponding letter at the same
position of the *to* parameter.


#### Examples
```R 
transformed_tuples <- code_transform_tuples("ACTG", "CAGT", c("ACG", "GAT"))
transformed_tuples <- code_transform_tuples("ACTG", "CAGT", "ACGGAT", tuple_length=3)
transformed_tuples <- code_transform_tuples("ACTG", "CAGT", "ACG GAT")

```
<hr>

### shift_tuples

#### Usage
```R 
shift_tuples(shifts, code, tuple_length = -55555L)
```

#### Arguments
 
*shifts*	number of shifts<br>

*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
shifted code as String vector


#### Description
 
This functions shifts all tuples in code anticlockwise. In other words, the first character of each tuples gets removed and
added to the end of the same tuple. Depending on the parameter *shift* this process is repeated multiple times.


#### Examples
```R 
shifted_code <- shift_tuples(2, c("ACG", "GAT"))
shifted_code <- shift_tuples(2, "ACGGAT", tuple_length=3)
shifted_code <- shift_tuples(2, "ACG GAT")

```
<hr>

## General circular code tools

### generate_code_by_min_value

#### Usage
```R 
generate_code_by_min_value(alphabet, tuple_length)
```

#### Arguments
 
*alphabet*	is a vector of letters.<br>

*tuple_length*	is the tuple length of the resulting code.<br>


#### Return
 
A maximal circular code as String vector.


#### Description
 
Based on a value function each word can be assigned to a value. The code is a set of the words with the
lowest value of each permutation class. This code has be proven to be circular and maximal. This can be done for any alphabet.


#### Examples
```R 
code <- generate_code_by_min_value(c("A", "C", "G", "T"), 3)

```
<hr>

### code_check_if_circular

#### Usage
```R 
code_check_if_circular(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Boolean value. True if the code is circular.


#### Description
 
This function checks if a code is circular. The code can either be a vector of tuples or a sequence. If the code
is a sequence an additional word length parameter is needed.
Circular codes are a block codes. We will call a set of tuples *X* of same length
a code if every concatenation of words *w* in *X* written on a circle has only a single decomposition into words from *X*.
It is used as an unproved approach to explain the
method used in gens to retrieving the correct reading frames of RNA.<br>
For more info on this subject read:<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_check_if_circular(c("ACG", "CAG"))
code_check_if_circular("ACGCAG", 3)
code_check_if_circular("ACG CAG")

```
<hr>

### code_check_if_cn_circular

#### Usage
```R 
code_check_if_cn_circular(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Boolean value. True if the code is Cn-circular.


#### Description
 
This function checks if a code is Cn-circular.
The code can either be a vector of tuples or a sequence. If the code
is a sequence an additional word length parameter is needed.<br>
Cn-circular means:<br>
That all circular permutations of the code (all tuples) are circular codes again.<br>
This is an extended property of the circular codes. Circular codes are a block codes. See *code_check_if_circular* for more details.<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_check_if_cn_circular(c("ACG", "CAG"))
code_check_if_cn_circular("ACGCAG", 3)
code_check_if_cn_circular("ACG CAG")

```
<hr>

### code_check_if_code

#### Usage
```R 
code_check_if_code(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Boolean value. True if the code is circular.


#### Description
 
This function checks if a code is a code.<br>
Let *Sigma* be a finite alphabet and X a subset of *Sigma**l for some l in N.<br>
- For w in *Sigma**l , an X-decomposition of w is a tuple (x1 ,... , xt ) in Xt with t in N such that
X = x 1 · x 2 · · · x t .
- A set X subset of *Sigma**l  is a code if each word w in X has a single X-decomposition.
- For an integer l > 1, an l-letter code is a code contained in .
Let X be a subset of *Sigma**l . X is called a code over Σ ∗ if for all n, m > 0 and x1...xn , x1...xm in X,
the condition<br>
x1...xn = x1...xm<br>
implies<br>
n = m and xi = xj for i = 1,..., n<br>
For more info on this subject read:<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_check_if_circular(c("ACG", "CAG"))
code_check_if_circular("ACGCAG", 3)
code_check_if_circular("ACG CAG")

```
<hr>

### code_check_if_comma_free

#### Usage
```R 
code_check_if_comma_free(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Boolean value. True if the code is comma free.


#### Description
 
This function checks if a code is comma free.
The code can either be a vector of tuples or a sequence. If the code
is a sequence an additional word length parameter is needed.<br>
Comma free is a more restrictive code of the family of the circular codes:<br>
A comma-free code is block code in which no concatenation of two code words contains a valid code word that overlaps both.<br>
This is an extended property of the circular codes. Circular codes are a block codes. See *code_check_if_circular* for more details.<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_check_if_comma_free(c("ACG", "CAG"))
code_check_if_comma_free("ACGCAG", 3)
code_check_if_comma_free("ACG CAG")

```
<hr>

### code_check_if_k_circular

#### Usage
```R 
code_check_if_k_circular(k, code, tuple_length = -55555L)
```

#### Arguments
 
*k*	is is integer. k refers to the k-circular property.<br>

*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Boolean value. True if the code is k-circular.


#### Description
 
This function checks if a code is k-circular.
The code can either be a vector of tuples or a sequence. If the code
is a sequence an additional word length parameter is needed.<br>
k-circular means:<br>
That for each sequence/concatenation of less than k tuples of a code *X* written on a circle, there is only one partition in tuples from the code *X*.
This is an extended property of the circular codes. Circular codes are a block codes. See *code_check_if_circular* for more details.<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_check_if_k_circular(2, c("ACG", "CAG"))
code_check_if_k_circular(2, "ACGCAG", 3)
code_check_if_k_circular(2, "ACG CAG")

```
<hr>

### code_k_value

#### Usage
```R 
code_k_value(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
k value of a k-circular code.


#### Description
 
This function get the k value of a code which is k-circular.
The code can either be a vector of tuples or a sequence. If the code
is a sequence an additional word length parameter is needed.<br>
k-circular means:<br>
That for each sequence/concatenation of less than k tuples of a code *X* written on a circle, there is only one partition in tuples from the code *X*.
This is an extended property of the circular codes. Circular codes are a block codes. See *code_check_if_circular* for more details.<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_k_value(c("ACG", "CAG"))
code_k_value("ACGCAG", 3)
code_k_value("ACG CAG")

```
<hr>

### seq_get_tuple_count

#### Usage
```R 
seq_get_tuple_count(seq, tuple_length = 3L)
```

#### Arguments
 
*tuple_length*	a number, the length of the block or tuple used<br>

*a*	character string a sequence of letters and/or numbers<br>


#### Return
 
Key value map of the words in the sequence


#### Description
 
Returns a table with all words in a sequence. For each word, the table shows how often the word appears in the sequence.


#### Examples
```R 
res <- seq_get_tuple_count("ACGCGAACG", 3)

```
<hr>

### seq_get_info

#### Usage
```R 
seq_get_info(seq, tuple_length = 3L)
```

#### Arguments
 
*tuple_length*	a number, the length of the block or tuple used<br>

*a*	character string a sequence of letters and/or numbers<br>


#### Return
 
A named list with the listed values:<br>
*alphabet* (String) All letters and symbols used.<br>
*number_of_tuple* (Number) The number of all words/tuples used.<br>
*tuple_count* (Key value map) Key value map of the words in the sequence.<br>


#### Description
 
Returns a table with all words in a sequence. For each word, the table shows how often the word appears in the sequence.


#### Examples
```R 
res <- seq_get_info("ACGCGAACG", 3)

```
<hr>

### find_and_analysis_code_in_sequence

#### Usage
```R 
find_and_analysis_code_in_sequence(
  seq,
  code,
  tuple_length = -55555L,
  frame = 0L
)
```

#### Arguments
 
*seq*	a character string a sequence of letters and/or numbers<br>

*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Returns a List with all analysing results. The list contains the following:<br>
*words* (String vector) all found words of the code in the sequence in the correct order.<br>
*idx_list* (Number vector) the first-letter index of all found words of the code in the sequence in the correct order.<br>
*rest* (String) all parts of the sequence which are not matching the code.<br>
*parts* (String vector) the sequence separated in matching and non matching parts. Odd indexes are matching, even indexes are not matching.<br>
*longest_match* (Number) the longest connected matching sequence.<br>
*total_match_in_percent* (Number) the percentage of the matching parts.<br>
*circularPermutations* (Number vector) list the circular per


#### Description
 
Finds all appearances of a code in a sequence. Finds the longest connected motive of words of the code in the sequence.
The function also calculates the matching bases of the found words in the sequence.


#### Examples
```R 
seq <- "ACGTCGCGACGTACGACGTCGTACTCGATGCAAGATC"
res <- find_and_analysis_code_in_sequence(seq, c("ACG", "TCG"))
res <- find_and_analysis_code_in_sequence(seq, "ACGCG", tuple_length=3)
res <- find_and_analysis_code_in_sequence(seq, "ACG TCG")

```
<hr>

## Graph based functions

### code_factor_cycle

#### Usage
```R 
code_factor_cycle(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
A igraph (<http://igraph.org/r/>) object: Edges and vertices of only the cycles of an graph representing a circular code.


#### Description
 
Prepares a R igraph object. Extracts all circular paths of the Graph G(X).
If the graph shows no cycle the graph will be empty. Otherwise it returns a igraph object showing all
circular paths.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
G <- code_factor_cycle(c("ACG", "CAG"))
G <- code_factor_cycle("ACGCAG", tuple_length=3)
G <- code_factor_cycle("ACG CAG")
plot(G)

```
<hr>

### code_factor_graph

#### Usage
```R 
code_factor_graph(
  code,
  show_cycles = FALSE,
  show_longest_path = FALSE,
  tuple_length = -55555L
)
```

#### Arguments
 
*code*	is either a string vector or a string.<br>

*show_cycles*	A bool value. If true the all edges which are part of a cycle are colored red.<br>

*show_longest_path*	A bool value. If true the all edges part of the longest path are colored blue.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
A igraph (<http://igraph.org/r/>) object: A graph representing a circular code.


#### Description
 
This function factors a igraph (<http://igraph.org/r/>) object of an representing graph of a circular code.
The following definition describes a directed graph to an n-nucleotide code.
Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
ordered pairs [v,w] in this case.<br>
Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
(V (X),E(X)) with set of vertices V (X) and set of edges E(X) as follows:
N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5<br>
V (X) = \{N1...Ni,Ni+1...Nn : N1N2N3...Nn in X, 0 < i < n\}<br>
E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3...Nn in X, 0 < i < n\}<br>
The graph G(X) is called the representing graph of X or the graph associated to X.<br>
Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
G <- code_factor_graph(c("ACG", "CAG"), TRUE, TRUE)
G <- code_factor_graph("ACGCAG", tuple_length=3, show_cycles=TRUE, show_longest_path=TRUE)
G <- code_factor_graph("ACG CAG", TRUE, TRUE)
plot(G)

```
<hr>

### code_factor_longest_path

#### Usage
```R 
code_factor_longest_path(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
A igraph (<http://igraph.org/r/>) object: Edges and vertices of only the longest path of an graph representing a circular code.


#### Description
 
Prepares a R igraph object. Extracts all longest path of the Graph G(X).
If the graph shows a cycle the graph will be empty. Otherwise it returns a igraph object showing all
longest paths.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
G <- code_factor_longest_path(c("ACG", "CAG"))
G <- code_factor_longest_path("ACGCAG", tuple_length=3)
G <- code_factor_longest_path("ACG CAG")
plot(G)

```
<hr>

### code_get_one_cycles_as_vector

#### Usage
```R 
code_get_one_cycles_as_vector(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
List of nodes representing a circular path in G(X).


#### Description
 
Prepares a R path string vector. Extracts all cycles in the Graph G(X).
If the graph has no cycles the vector will be empty. Otherwise it returns a vector with the nodes of
a circular path.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
l_graph <- code_get_one_cycles_as_vector(c("ACG", "CGA"))
l_graph <- code_get_one_cycles_as_vector("ACGCGA", 3)
l_graph <- code_get_one_cycles_as_vector("ACG CGA")

```
<hr>

### code_get_one_longest_path_as_vector

#### Usage
```R 
code_get_one_longest_path_as_vector(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
A String vector. Nodes of the longest path


#### Description
 
Prepares a R path string vector. Extracts all longest paths of the Graph G(X) and returns the tuples of the first found one.
If the graph shows a cycle the vector will be empty. Otherwise it returns a vector with one longest path.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
l_path <- code_get_one_circle_as_vector(c("ACG", "CGA"))
l_path <- code_get_one_circle_as_vector("ACGCGA", 3)
l_path <- code_get_one_circle_as_vector("ACG CGA")

```
<hr>

### code_get_all_cycles_as_vector

#### Usage
```R 
code_get_all_cycles_as_vector(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
List of nodes representing a circular path in G(X).


#### Description
 
Prepares a list of R path string vector. Extracts all cycles in the Graph G(X).
If the graph has no cycles the vector will be empty. Otherwise it returns a list of vectors with the nodes of
the circular paths.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
l_graph <- code_get_one_cycles_as_vector(c("ACG", "CGA"))
l_graph <- code_get_one_cycles_as_vector("ACGCGA", 3)
l_graph <- code_get_one_cycles_as_vector("ACG CGA")

```
<hr>

### code_get_all_longest_path_as_vector

#### Usage
```R 
code_get_all_longest_path_as_vector(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
A list of String vectors. Nodes of the longest path


#### Description
 
Prepares a list of R path string vector. Extracts all longest paths of the Graph G(X) and returns a list.
If the graph shows a cycle the vector will be empty. Otherwise it returns a list of vector with all longest paths.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
l_path <- code_get_all_longest_path_as_vector(c("ACG", "CGA"))
l_path <- code_get_all_longest_path_as_vector("ACGCGA", 3)
l_path <- code_get_all_longest_path_as_vector("ACG CGA")

```
<hr>

### code_path_end_vertices_miner

#### Usage
```R 
code_path_end_vertices_miner(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
list of vertices


#### Description
 
This function finds all vertices which have no outgoing edges in the associated graph.


#### Examples
```R 
vertices <- code_path_end_vertices_miner(c("ACG", "GAT"))
vertices <- code_path_end_vertices_miner("ACGGAT", tuple_length=3)
vertices <- code_path_end_vertices_miner("ACG GAT")

```
<hr>

## Genetic circular codes tools

### genetic_codes_as_df_by_index

#### Usage
```R 
genetic_codes_as_df_by_index(idx, acid = "RNA")
```

#### Arguments
 
*idx*	the index of a Genetic Code table as int. (check *print_all_translation_table*)<br>

*a@param*	acid a String, is optional: DNA or RNA<br>


#### Return
 
Returns a named List with all codons and the translated amino acids:<br>


#### Description
 
\*genetic_codes_as_df_by_index* returns a data.frame table which represents a Genetic Code. The table is 4*16.
This table has row names and column names.
<br> Source:<br>
*Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.*<br>
*Last update of the Genetic Codes: Nov. 18, 2016*
**{*https:#www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi*}


#### Examples
```R 
(code <- genetic_codes_as_df_by_index(1))

```
<hr>

### genetic_codes_by_index

#### Usage
```R 
genetic_codes_by_index(idx, acid = "DNA")
```

#### Arguments
 
*idx*	the index of a Genetic Code table as int. (check *print_all_translation_table*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
Returns a named List with all codons and the translated amino acids:<br>


#### Description
 
*genetic_codes_by_index* returns a list representing a Genetic Code. The list contains two arrays, one array of the codons and one array of the translated amino acids in the same order.
<br> Source:<br>
*Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.*<br>
*Last update of the Genetic Codes: Nov. 18, 2016*
**{*https://www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi*}


#### Examples
```R 
(code <- genetic_codes_by_index(1))

```
<hr>

### genetic_codes_by_name

#### Usage
```R 
genetic_codes_by_name(name, acid = "RNA")
```

#### Arguments
 
*name*	the name of a Genetic Code as string. (check *print_all_translation_table*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
Returns a named List with all codons and the translated amino acids:<br>


#### Description
 
*genetic_codes_by_name* returns a list representing a Genetic Code. The list contains two arrays, one array of the codons and one
array of the translated amino acids in the same order.<br>
Source:<br>
*Compiled by Andrzej (Anjay) Elzanowski and Jim Ostell at National Center for Biotechnology Information (NCBI), Bethesda, Maryland, U.S.A.*<br>
*Last update of the Genetic Codes: Nov. 18, 2016*
**{*https://www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi*}


#### Examples
```R 
(code <- genetic_codes_by_name("The Yeast Mitochondrial Code"))

```
<hr>

### print_all_translation_tables

#### Usage
```R 
print_all_translation_tables()
```

#### Arguments
 \-

#### Return
 \-

#### Description
 
*print_all_translation_tables* prints a list of the genetic codes contained by this project. The list includes names and indexes of the codes.


#### Examples
```R 
print_all_translation_tables()

```
<hr>

### code_strip_complements

#### Usage
```R 
code_strip_complements(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It has to be a RNA/DNA - code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
a string the code reduced to a strongly comma-free code


#### Description
 
This function removes one codon of each codon anti-codon pair. (see  *code_check_if_self_complementary*)


#### Examples
```R \-```
<hr>

### code_check_if_self_complementary

#### Usage
```R 
code_check_if_self_complementary(code, tuple_length = -55555L, mute = TRUE)
```

#### Arguments
 
*code*	is either a string vector or a string. It has to be a RNA/DNA - code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>

*mute*	set false to get console output information about not self-complementary tuples.<br>


#### Return
 
Boolean value. True if the code is self-complementary.


#### Description
 
This function checks if a code is self complementary.
The code can either be a vector of DNA/RNA tuples or a sequence. If the code
is a sequence an additional word length parameter is needed.<br>
A code is self complementary if and only if for all tuples in the code the anti-tuple is also in the code.
An anti-tuple is te reversed tuple of complementary bases.<br> A <-> T (U) and C <-> G. The anti-tuple of ACG is CGT
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_check_if_self_complementary(c("ACG", "CAG"))
code_check_if_self_complementary("ACGCAG", 3)
code_check_if_self_complementary("ACG CAG")

```
<hr>

### code_get_acid

#### Usage
```R 
code_get_acid(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It should be a RNA/DNA - code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
String value. One of NONE, DNA, RNA


#### Description
 
Returns either RNA or DNA depending on the codes Bases. If the code contains only CYTOSINE (C), ADENINE (A), GUANINE (G)
the functions returns DNA. If the code contains THYMINE (T) it will also return DNA. On the other side, if the
the code contains URACIL (U) bases the function returns RNA. If the code contains URACIL (U) and THYMINE (T) or any other letter
then CYTOSINE (C), ADENINE (A), GUANINE (G), URACIL (U) or THYMINE (T) it will return NONE
For more info on this subject read:<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_get_acid(c("ACG", "CAG"))
code_get_acid("ACGCAG", 3)
code_get_acid("ACG CAG")

```
<hr>

### code_is_translatable

#### Usage
```R 
code_is_translatable(code, tuple_length = -55555L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple/word length of the code.<br>


#### Return
 
Boolean value. True if a fitting translation table exists.


#### Description
 
This function checks if a code can be translated into amino acids. Therefore, it simply checks if a translation table which fits the tuple size of the code
is in the system.<br>.
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_is_translatable(c("ACG", "CAG"))
code_is_translatable("ACGCAG", 3)
code_is_translatable("ACG CAG")

```
<hr>

### code_get_all_amino_acids

#### Usage
```R 
code_get_all_amino_acids(code, idx_trans_table = 1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It should be a RNA/DNA - code or a sequence.<br>

*idx_trans_table*	the index of a Genetic Code translation table as int. (see *print_all_translation_table*)<br>


#### Return
 
String vector. list of amino acids


#### Description
 
Returns the amino acids which are encoded by a codes. It returns a list of amino acids in the same order as the code. The code can contain only CYTOSINE (C), ADENINE (A), GUANINE (G)
and THYMINE (T) or URACIL (U) bases. If no other translation table is selecte the function will use the 
*standard genetic code*. A different tranlastion table has to be added by index. Therefore, (see *print_all_translation_tables*)<br>
For more info on this subject read:<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_get_all_amino_acids(c("ACG", "CAG"), idx_trans_table=2)
code_get_all_amino_acids("ACGCAG", idx_trans_table=2)
code_get_all_amino_acids("ACG CAG", idx_trans_table=2)

```
<hr>

### code_get_amino_acids

#### Usage
```R 
code_get_amino_acids(code, idx_trans_table = 1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It should be a RNA/DNA - code or a sequence.<br>

*idx_trans_table*	the index of a Genetic Code table as int. (check *print_all_translation_table*)<br>


#### Return
 
String vector. list of amino acids


#### Description
 
Returns a set of all the amino acids which are encoded by the codes. The code can contain only CYTOSINE (C), ADENINE (A), GUANINE (G)
and THYMINE (T) or URACIL (U) bases. If no other translation table is selecte the function will use the 
*standard genetic code*. A different tranlastion table has to be added by index. Therefore, (see *print_all_translation_tables*)<br>
For more info on this subject read:<br>
*https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5492142/*,<br>
*http://dpt-info.u-strasbg.fr/~c.michel/Circular_Codes.pdf*,<br>
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_get_amino_acids(c("ACG", "CAG"), idx_trans_table=2)
code_get_amino_acids("ACGCAG", idx_trans_table=2)
code_get_amino_acids("ACG CAG", idx_trans_table=2)

```
<hr>

### code_named_transform_tuples

#### Usage
```R 
code_named_transform_tuples(trans_name, code, tuple_length = -55555L)
```

#### Arguments
 
*trans_name*	tname of a transformation. listed in description.<br>

*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
transformed code as String vector


#### Description
 
This function transforms all tuples in code. The single letters get transformed by the rules which are set as parameter.
The rules are the predefined and listed below. This only works for genetic gen codes and sequences<br>


#### Examples
```R 
transformed_tuples <- code_named_transform_tuples("I", c("ACG", "GAT"))
transformed_tuples <- code_named_transform_tuples("SW", "ACGGAT", tuple_length=3)
transformed_tuples <- code_named_transform_tuples("SW", "ACG GAT")

```
<hr>

### codons_to_tessera

#### Usage
```R 
codons_to_tessera(code)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>


#### Return
 
the argument code transfomed to a set of tesserae


#### Description
 
This function uses a transformation to map all codons to a tessera. This transformation was published by Gonzalez, Giannerini and Rosa.


#### Examples
```R 
tessera <- codons_to_tessera(c("ACG", "GAT"))
tessera <- codons_to_tessera("ACGGAT")
tessera <- codons_to_tessera("ACG GAT")

```
<hr>

### code_check_if_tessera

#### Usage
```R 
code_check_if_tessera(code)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>


#### Return
 
if code only contains tessera


#### Description
 
This function checks if all words in the code are correct Tessera words.


#### Examples
```R 
is_tessera <- code_check_if_tessera(c("ACGT", "GATC"))
is_tessera <- code_check_if_tessera("ACGTGATC" )
is_tessera <- code_check_if_tessera("ACGT GATC")

```
<hr>

### get_rna_bases

#### Usage
```R 
get_rna_bases()
```

#### Arguments
 \-

#### Return
 
{"U", "C", "A", "G"}


#### Description
 
Returns all RNA bases


#### Examples
```R 
res <- get_rna_bases()

```
<hr>

### get_rna_codon_list

#### Usage
```R 
get_rna_codon_list()
```

#### Arguments
 \-

#### Return
 
A vector object with all RNA codons


#### Description
 
get_rna_codon_list will generate the following list:<br>
UUU UCU UAU UGU UUC UCC UAC UGC UUA UCA UAA UGA UUG UCG UAG UGG CUU CCU CAU CGU CUC CCC CAC CGC CUA CCA CAA CGA CUG CCG CAG CGG
AUU ACU AAU AGU AUC ACC AAC AGC AUA ACA AAA AGA AUG ACG AAG AGG GUU GCU GAU GGU GUC GCC GAC GGC GUA GCA GAA GGA GUG GCG GAG GGG


#### Examples
```R 
res <- get_rna_codon_list()

```
<hr>

### get_rna_codon_table

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)

#### Usage
```R 
get_rna_codon_table()
```

#### Arguments
 \-

#### Return
 
A matrix object with all RNA codons


#### Description
 
get_rna_codon_table will generate a 4*16 table based on the following list:<br>
UUU UCU UAU UGU<br>
AUU ACU AAU AGU<br>


#### Examples
```R 
res <- get_rna_codon_table()

```
<hr>

### get_dna_bases

#### Usage
```R 
get_dna_bases()
```

#### Arguments
 \-

#### Return
 
{"T", "C", "A", "G"}


#### Description
 
Returns all DNA bases


#### Examples
```R 
res <- get_dna_bases ()

```
<hr>

### get_dna_codon_list

#### Usage
```R 
get_dna_codon_list()
```

#### Arguments
 \-

#### Return
 
A vector object with all DNA codons


#### Description
 
get_dna_codon_list will generate the following list:<br>
TTT TCT TAT TGT TTC TCC TAC TGC TTA TCA TAA TGA TTG TCG TAG TGG CTT CCT CAT CGT CTC CCC CAC CGC CTA CCA CAA CGA CTG CCG CAG CGG
ATT ACT AAT AGT ATC ACC AAC AGC ATA ACA AAA AGA ATG ACG AAG AGG GTT GCT GAT GGT GTC GCC GAC GGC GTA GCA GAA GGA GTG GCG GAG GGG


#### Examples
```R 
res <- get_dna_codon_list()

```
<hr>

### get_dna_codon_table

#### Usage
```R 
get_dna_codon_table()
```

#### Arguments
 \-

#### Return
 
A matrix object with all DNA codons


#### Description
 
get_dna_codon_table will generate a 4*16 table based on the following list:<br>
 TTT TCT TAT TGT<br>
 TTC TCC TAC TGC<br>
 TTA TCA TAA TGA<br>
 TTG TCG TAG TGG<br>
 CTT CCT CAT CGT<br>
 CTC CCC CAC CGC<br>
 CTA CCA CAA CGA<br>
 CTG CCG CAG CGG<br>
 ATT ACT AAT AGT<br>
 ATC ACC AAC AGC<br>
 ATA ACA AAA AGA<br>
 ATG ACG AAG AGG<br>
 GTT GCT GAT GGT<br>
 GTC GCC GAC GGC<br>
 GTA GCA GAA GGA<br>
 GTG GCG GAG GGG


#### Examples
```R 
res <- get_rna_codon_table()

```
<hr>

### code_pdf_report

#### Usage
```R 
code_pdf_report(code, tuple_length = -55555)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 \-

#### Description
 
The function makes a dir called: "GCATR_Report" in your current working dir. In the following steps it cops a .Rnw template file
into the new dir. Afterwords it executes knitr with parameters based on the your input. All the generated files are in the new dir.


#### Examples
```R 
code_pdf_report(c("ACG", "CAG"))
code_pdf_report("ACGCAG", 3)
code_pdf_report("ACG CAG")


```
<hr>

## Conductance

### get_average_conductance_of_code

#### Usage
```R 
get_average_conductance_of_code(codeName, acid = "DNA")
```

#### Arguments
 
*codeName*	a String, the name of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
A Number, the average conductance of a genetic translation table


#### Description
 
This function calculates the average conductance for a selected genetic translation table.
The conductance is a number which reflects the robustness of a genetic translation table.
The conductance the ration of the codons translating one amino acid which differ in only one position and the
codons translating the same amino acid but differ in more then one position.


#### Examples
```R 
ac = get_average_conductance_of_code("The Standard Code")
ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
```
<hr>

### get_average_conductance_of_codeidx

#### Usage
```R 
get_average_conductance_of_codeidx(codeIdx, acid = "DNA")
```

#### Arguments
 
*codeIdx*	a Number, the index of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
A Number, the average conductance of a genetic translation table


#### Description
 
This function calculates the average conductance for a selected genetic translation table.
The conductance is a number which reflects the robustness of a genetic translation table.
The conductance the ration of the codons translating one amino acid which differ in only one position and the
codons translating the same amino acid but differ in more then one position.


#### Examples
```R 
ac = get_average_conductance_of_code("The Standard Code")
ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
```
<hr>

### get_max_conductance_of_code

#### Usage
```R 
get_max_conductance_of_code(codeName, acid = "DNA")
```

#### Arguments
 
*codeName*	a String, the name of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
A Number, the max conductance of a genetic translation table


#### Description
 
This function calculates the max conductance for a selected genetic translation table.
The conductance is a number which reflects the robustness of a genetic translation table.
The conductance the ration of the codons translating one amino acid which differ in only one position and the
codons translating the same amino acid but differ in more then one position.


#### Examples
```R 
ac = get_average_conductance_of_code("The Standard Code")
ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
```
<hr>

### get_max_conductance_of_codeidx

#### Usage
```R 
get_max_conductance_of_codeidx(codeIdx, acid = "DNA")
```

#### Arguments
 
*codeIdx*	a Number, the index of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
A Number, the max conductance of a genetic translation table


#### Description
 
This function calculates the max conductance for a selected genetic translation table.
The conductance is a number which reflects the robustness of a genetic translation table.
The conductance the ration of the codons translating one amino acid which differ in only one position and the
codons translating the same amino acid but differ in more then one position.


#### Examples
```R 
ac = get_average_conductance_of_code("The Standard Code")
ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
```
<hr>

### get_min_conductance_of_code

#### Usage
```R 
get_min_conductance_of_code(codeName, acid = "DNA")
```

#### Arguments
 
*codeName*	a String, the name of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
A Number, the min conductance of a genetic translation table


#### Description
 
This function calculates the min conductance for a selected genetic translation table.
The conductance is a number which reflects the robustness of a genetic translation table.
The conductance the ration of the codons translating one amino acid which differ in only one position and the
codons translating the same amino acid but differ in more then one position.


#### Examples
```R 
ac = get_average_conductance_of_code("The Standard Code")
ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
```
<hr>

### get_min_conductance_of_codeidx

#### Usage
```R 
get_min_conductance_of_codeidx(codeIdx, acid = "DNA")
```

#### Arguments
 
*codeIdx*	a Number, the index of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String [optional]: The value must be DNA or RNA<br>


#### Return
 
A Number, the min conductance of a genetic translation table


#### Description
 
This function calculates the min conductance for a selected genetic translation table.
The conductance is a number which reflects the robustness of a genetic translation table.
The conductance the ration of the codons translating one amino acid which differ in only one position and the
codons translating the same amino acid but differ in more then one position.


#### Examples
```R 
ac = get_average_conductance_of_code("The Standard Code")
ac = get_average_conductance_of_code("The Vertebrate Mitochondrial Code", "RNA")
```
<hr>

## Binary Dichotomic Algorithm (BDA)

### BDATools

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)

#### Usage
```R \-```

#### Arguments
 \-

#### Return
 \-

#### Description
 
This Object contains a binary dichotomic algorithm (BDA) procedure. Use *start_bda* or *code_start_bda* to get a BDATools object. <br> 
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
bda_obj <- start_bda()
add_rule(bda_obj, 1, 2, "C", "G", "A", "U")
add_rule(bda_obj, 1, 3, "A", "G", "C", "U")
res <- run_bda_as_matrix(bda_obj)

```
<hr>

### start_bda

#### Usage
```R 
start_bda()
```

#### Arguments
 \-

#### Return
 
Boolean value. True if the procedure has started


#### Description
 
This Function starts a binary dichotomic algorithm (BDA) procedure for all codons (see *get_rna_codon_list*).
To run *run_bda_as_matrix* the BDA procedure has been started by this (*start_bda*) function.
Each added binary BDA results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call *code_start_bda* or to start a procedure
for all RNA codons call *start_bda*.
To add a BDA simply Call *add_rule*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
bda_obj <- start_bda()
add_rule(bda_obj, 1, 2, "C", "G", "A", "U")
add_rule(bda_obj, 1, 3, "A", "G", "C", "U")
res <- run_bda_as_matrix(bda_obj)

```
<hr>

### code_start_bda

#### Usage
```R 
code_start_bda(code, tuple_length = -55555)
```

#### Arguments
 
*code*	is either a string vector or a string. It can be a DNA or RNA sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Boolean value. True if the procedure has started


#### Description
 
Each added binary dichotomic algorithm (BDA) results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call *code_start_bda* or to start a procedure
for all RNA codons call *start_bda*.
To add a BDA simply Call *add_rule*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
bda_obj <- code_start_bda(c("ACG", "CAG")) # or
bda_obj <- code_start_bda("ACG CAG")       # or
bda_obj <- code_start_bda("ACGCAG", tuple_length=3)
add_rule(bda_obj, 1, 2, "C", "G", "A", "T")
res.binary <- run_bda(bda_obj)

```
<hr>

### add_rule

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/bda_diagramm.png?raw=true)

#### Usage
```R 
add_rule(bda_obj, i_1, i_2, Q_11, Q_12, Q_21, Q_22)
```

#### Arguments
 
*bda_obj*	BDA object (see *BDATools*)<br>

*i_1*	A unsigend Integer from 1 - [WORD LENGTH]<br>

*i_2*	A unsigend Integer from 1 - [WORD LENGTH]<br>

*Q_11*	A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}<br>

*Q_12*	A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}<br>

*Q_21*	A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}<br>

*Q_22*	A single character. Has to be one of \{'A', 'C', 'G', 'T', 'U'\}<br>


#### Return
 
Boolean value. True if the rules parameters are correct


#### Description
 
Each added binary dichotomic algorithm (BDA) results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call *code_start_bda* or to start a procedure
for all RNA codons call *start_bda*.
To add a BDA simply Call *add_rule*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
bda_obj <- code_start_bda(c("ACG", "CAG"))
add_rule(bda_obj, 1, 2, "C", "G", "A", "T")
res.binary <- run_bda(bda_obj)

```
<hr>

### run_bda

#### Usage
```R 
run_bda(bda_obj)
```

#### Arguments
 
*bda_obj*	BDA object (see *BDATools*)<br>


#### Return
 
A List. A binary representation of the Code.


#### Description
 
This function executes the currently open binary dichotomic algorithm (BDA) procedure. Therefore, you need to start a BDA procedure.
You can call *code_start_bda* to start a procedure
for all codons call *start_bda*.
To add a BDA simply Call *add_rule*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
bda_obj<-code_start_bda(c("ACG", "CAG"))
add_rule(bda_obj, 1, 2, "C", "G", "A", "T")
add_rule(bda_obj, 1, 3, "A", "G", "C", "T")
res.binary <- run_bda(bda_obj)

```
<hr>

### run_bda_as_matrix

#### Usage
```R 
run_bda_as_matrix(bda_obj)
```

#### Arguments
 
*bda_obj*	BDA object (see *BDATools*)<br>


#### Return
 
Binary results as Matrix. For example:<br> "UUU -> 00" "UCU -> 10" "UAU -> 00" "UGU -> 10" <br> "UUC -> 00" "UCC -> 10" "UAC -> 00" "UGC -> 10" <br>  "UUA -> 01" "UCA -> 11" "UAA -> 01" "UGA -> 11" <br>  "UUG -> 01" "UCG -> 11" "UAG -> 01" "UGG -> 11" <br>  "CUU -> 00" "CCU -> 00" "CAU -> 00" "CGU -> 00" <br>  "CUC -> 00" "CCC -> 00" "CAC -> 00" "CGC -> 00" <br>  "CUA -> 01" "CCA -> 01" "CAA -> 01" "CGA -> 01" <br>  "CUG -> 01" "CCG -> 01" "CAG -> 01" "CGG -> 01" <br>  "AUU -> 00" "ACU -> 10" "AAU -> 00" "AGU -> 10" <br>  "AUC -> 00" "ACC -> 10" "AAC -> 00" "AGC -> 10" <br>  "AUA -> 00" "ACA -> 10" "AAA -> 00" "AGA -> 10" <br>  "AUG -> 00" "ACG -> 10" "AAG -> 00" "AGG -> 10" <br>  "GUU -> 11" "GCU -> 11" "GAU -> 11" "GGU -> 11" <br>  "GUC -> 11" "GCC -> 11" "GAC -> 11" "GGC -> 11" <br>  "GUA -> 11" "GCA -> 11" "GAA -> 11" "GGA -> 11" <br>  "GUG -> 11" "GCG -> 11" "GAG -> 11" "GGG -> 11"


#### Description
 
This Function executes a binary dichotomic algorithm (BDA) procedure. It only works if the BDA procedure has been started by the *start_bda* function.
Each added binary BDA results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call *code_start_bda* or to start a procedure
for all RNA codons call *start_bda*.
To add a BDA simply Call *add_rule*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
bda_obj <- start_bda()
add_rule(1, 2, "C", "G", "A", "U")
add_rule(1, 3, "A", "G", "C", "U")
res <- run_bda_as_matrix(bda_obj)

```
<hr>

<!--doc-end-->


# Copyright and license
Code and documentation copyright 2018-2019 Mannheim University of Applied Sciences. Code released under the GPL License, Version 2.0.
