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
### [General Circular Codes](#general-circular-codes)

[code_check_if_circular](#code_check_if_circular)<br>
[code_check_if_k_circular](#code_check_if_k_circular)<br>
[code_check_if_cn_circular](#code_check_if_cn_circular)<br>
[code_check_if_comma_free](#code_check_if_comma_free)<br>
[find_and_analysis_code_in_sequence](#find_and_analysis_code_in_sequence)<br>
[generate_code_by_min_value](#generate_code_by_min_value)<br>
[shift_tuples](#shift_tuples)<br>

### [Graph based functions](#graph-based-functions)

[code_factor_graph](#code_factor_graph)<br>
[code_factor_cycle](#code_factor_cycle)<br>
[code_factor_longest_path](#code_factor_longest_path)<br>
[code_factor_c3graph](#code_factor_c3graph)<br>

[code_prepare_factor_graph](#code_prepare_factor_gen_c3graph)<br>
[code_prepare_factor_all_cycle](#code_prepare_factor_all_cycle)<br>
[code_prepare_factor_longest_path](#code_prepare_factor_longest_path)<br>
[code_prepare_factor_gen_c3graph](#code_prepare_factor_gen_c3graph)<br>

[code_get_one_cycles_as_vector](#code_get_one_cycles_as_vector)<br>
[code_get_all_cycles_as_vector](#code_get_all_cycles_as_vector)<br>
[code_get_one_longest_path_as_vector](#code_get_one_longest_path_as_vector)<br>
[code_get_all_longest_path_as_vector](#code_get_all_longest_path_as_vector)<br>

### [Genetic Circular Codes](#generic-circular-codes)

[code_check_if_self_complementary](#code_check_if_self_complementary)<br>
[code_get_acid](#code_get_acid)<br>
[get_dna_bases](#get_dna_bases)<br>
[get_rna_bases](#get_rna_bases)<br>
[get_rna_codon_table](#get_rna_codon_table)<br><!--accessory:[![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)]-->
[get_rna_codon_list](#get_rna_codon_list)<br>

[print_all_translation_tables](#print_all_translation_tables)<br>
[genetic_codes_by_index](#genetic_codes_by_index)<br>
[genetic_codes_by_name](#genetic_codes_by_name)<br>

[get_average_conductance_of_codeidx](#get_average_conductance_of_codeidx)<br>
[get_max_conductance_of_codeidx](#get_max_conductance_of_codeidx)<br>
[get_min_conductance_of_codeidx](#get_min_conductance_of_codeidx)<br>
[get_average_conductance_of_code](#get_average_conductance_of_code)<br>
[get_max_conductance_of_code](#get_max_conductance_of_code)<br>
[get_min_conductance_of_code](#get_min_conductance_of_code)<br>

### [Binary Dichotomic Algorithm (BDA)](#binary_dichotomic_algorithm_(BDA))

[start_bda](#start_bda)<br><!--accessory:[![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)]-->
[code_start_bda](#code_start_bda)<br>
[add_bda](#add_bda)<br><!--accessory:[![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/bda_diagramm.png?raw=true)]-->
[run_bda](#run_bda)<br>
[run_bda_as_matrix](#run_bda_as_matrix)<br>

<!--outline-end-->

<!--doc-start-->
## General Circular Codes

### code_check_if_circular

#### Usage
```R 
code_check_if_circular(code, length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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

### code_check_if_k_circular

#### Usage
```R 
code_check_if_k_circular(k, code, length = -1L)
```

#### Arguments
 
*k*	is is integer. k refers to the k-circular property.<br>

*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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

### code_check_if_cn_circular

#### Usage
```R 
code_check_if_cn_circular(code, length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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

### code_check_if_comma_free

#### Usage
```R 
code_check_if_comma_free(code, length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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

### find_and_analysis_code_in_sequence

#### Usage
```R 
find_and_analysis_code_in_sequence(seq, code, tuple_length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
Returns a List with all analysing results. The list contains the following:<br>
*words* (String vector) all found words of the code in the sequence in the correct order.<br>
*idx_list* (Number vector) the first-letter index of all found words of the code in the sequence in the correct order.<br>
*rest* (String) all parts of the sequence which are not matching the code.<br>
*parts* (String vector) the sequence separated in matching and non matching parts. Odd indexes are matching, even indexes are not matching.<br>
*longest_match* (Number) the longest connected matching sequence.<br>
*total_match_in_percent* (Number) the percentage of the matching parts.


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

### shift_tuples

#### Usage
```R 
shift_tuples(shifts, code, tuple_length = -1L)
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

## Graph based functions

### code_factor_graph

#### Usage
```R 
code_factor_graph(code, show_cycles = FALSE, show_longest_path = FALSE,
  tuple_length = -1)
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

### code_factor_cycle

#### Usage
```R 
code_factor_cycle(code, tuple_length = -1)
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

### code_factor_longest_path

#### Usage
```R 
code_factor_longest_path(code, tuple_length = -1)
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

### code_factor_c3graph

#### Usage
```R 
code_factor_c3graph(code, tuple_length = -1)
```

#### Arguments
 
*code*	is either a string vector or a string. It can be a DNA or RNA sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
List:  A igraph (<http://igraph.org/r/>) object: A graph representing a circular code with C3 extension..


#### Description
 
This function factors a igraph (<http://igraph.org/r/>) object of an representing graph of a circular code.
The difference to the standard Graph is that the edges of the shifted (circular permutated) Codes
of the the origin code are included as undirected edges.<br>
The following definition describes a directed graph to an n-nucleotide code.
Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
ordered pairs [v,w] in this case.<br>
Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
(V (X), EU(X) ,E(X)) with set of vertices V (X), a set of undirected edges EU(X) and set of edges E(X) as follows:
N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5<br>
V (X) = \{N1...Ni,Ni+1...N3 : N1N2N3...Nn in X, 0 < i < 3\}<br>
EU (X) = \{[N2,N3N1] : N1N2N3 in X\}<br>
E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3 in X, 0 < i < 3\}<br>
The graph G(X) is called the representing graph of X or the graph associated to X.<br>
Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
G <- code_prepare_factor_gen_c3graph(c("ACG", "CAG"))
G <- code_prepare_factor_gen_c3graph("ACGCAG", tuple_length=3)
G <- code_prepare_factor_gen_c3graph("ACG CAG")
plot(G)

```
<hr>

### code_prepare_factor_graph

#### Usage
```R 
code_prepare_factor_graph(code, show_cycles = FALSE,
  show_longest_path = FALSE, tuple_length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can be a DNA or RNA sequence.<br>

*show_cycles*	A bool value. If true the all edges which are part of a cycle are colored red.<br>

*show_longest_path*	A bool value. If true the all edges part of the longest path are colored blue.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
List: Edges and vertices of an graph representing a circular code.


#### Description
 
This function factors the set of edges and the set of vertices of an representing graph of a circular code.
This sets can be used to construct the graph. To get a graph object use *code_factor_graph*.
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
code_prepare_factor_graph(c("ACG", "CAG"), TRUE, TRUE)
code_prepare_factor_graph("ACGCAG", tuple_length=3, show_cycles=TRUE, show_longest_path=TRUE)
code_prepare_factor_graph("ACG CAG", TRUE, TRUE)

```
<hr>

### code_prepare_factor_all_cycle

#### Usage
```R 
code_prepare_factor_all_cycle(code, tuple_length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can be a DNA or RNA sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
List: Edges and vertices of only the cycles of an graph representing a circular code.


#### Description
 
This function is based on the represent graph of a circular code (see *code_prepare_factor_graph*).
The function only returns a list of edges and vertices. To get a graph object use *code_factor_cycle*.
The function checks if the code is circular. If the code is not circular the functions returns all cycles in the representing graph.
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_prepare_factor_all_cycle(c("ACG", "CAG"))
code_prepare_factor_all_cycle("ACGCAG", tuple_length=3)
code_prepare_factor_all_cycle("ACG CAG")

```
<hr>

### code_prepare_factor_longest_path

#### Usage
```R 
code_prepare_factor_longest_path(code, tuple_length = -1L)
```

#### Arguments
 
*code*	A vertor with codons.' @param length if code is a sequence, length is the tuple length of the code.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
List: Edges and vertices of only the longest path of an graph representing a circular code.


#### Description
 
This function is based on the represent graph of a circular code (see *code_prepare_factor_graph*).
The function only returns a list of edges and vertices. To get a graph object use *code_factor_longest_path*.
The function checks if the code is circular. If the code is not circular the functions returns the logest paths.
*2007 Christian MICHEL. CIRCULAR CODES IN GENES*


#### Examples
```R 
code_prepare_factor_longest_path(c("ACG", "CAG"))
code_prepare_factor_longest_path("ACGCAG", tuple_length=3)
code_prepare_factor_longest_path("ACG CAG")

```
<hr>

### code_prepare_factor_gen_c3graph

#### Usage
```R 
code_prepare_factor_gen_c3graph(code, tuple_length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can be a DNA or RNA sequence.<br>

*tuple_length*	if code is a sequence, length is the tuple length of the code.<br>


#### Return
 
List: Edges and vertices of an C3-graph representing a circular code.


#### Description
 
This function factors the set of edges and the set of vertices of an representing graph of a circular code.
This sets can be used to construct the graph. To get a graph object use *code_factor_c3graph*.<br>
The difference to the standard Graph is that the edges of the shifted (circular permutated) Codes
of the the origin code are included as undirected edges.<br>
The following definition describes a directed graph to an n-nucleotide code.
Recall from graph theory (Clark and Holton, 1991) that a graph G consists of
a finite set of vertices (nodes) V and a finite set of edges E. Here, an edge is a set \{v,w\} of vertices
from V . The graph is called oriented if the edges have an orientation, i.e. edges are considered to be
ordered pairs [v,w] in this case.<br>
Definition 2.1. Let X Bn be an n-nucleotide code (n 2 N). We define a directed graph G(X) =
(V (X), EU(X) ,E(X)) with set of vertices V (X), a set of undirected edges EU(X) and set of edges E(X) as follows:
N-NUCLEOTIDE CIRCULAR CODES IN GRAPH THEORY 5<br>
V (X) = \{N1...Ni,Ni+1...N3 : N1N2N3...Nn in X, 0 < i < 3\}<br>
EU (X) = \{[N2,N3N1] : N1N2N3 in X\}<br>
E(X) = \{[N1...Ni,Ni+1...Nn] : N1N2N3 in X, 0 < i < 3\}<br>
The graph G(X) is called the representing graph of X or the graph associated to X.<br>
Basically, the graph G(X) associated to a code X interprets n-nucleotide words from X in (n−1) ways
by pairs of i-nucleotides and (n-i)-nucleotides for 0 < i < n.<br>
*2007 E. FIMMEL, C. J. MICHEL, AND L. STRÜNGMANN. N-nucleotide circular codes in graph theory*


#### Examples
```R 
code_prepare_factor_gen_c3graph(c("ACG", "CAG"))
code_prepare_factor_gen_c3graph("ACGCAG", tuple_length=3)
code_prepare_factor_gen_c3graph("ACG CAG")

```
<hr>

### code_get_one_cycles_as_vector

#### Usage
```R 
code_get_one_cycles_as_vector(code, tuple_length = -1L)
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

### code_get_all_cycles_as_vector

#### Usage
```R 
code_get_all_cycles_as_vector(code, tuple_length = -1L)
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

### code_get_one_longest_path_as_vector

#### Usage
```R 
code_get_one_longest_path_as_vector(code, length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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

### code_get_all_longest_path_as_vector

#### Usage
```R 
code_get_all_longest_path_as_vector(code, length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It can either be a code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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

## Genetic Circular Codes

### code_check_if_self_complementary

#### Usage
```R 
code_check_if_self_complementary(code, length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It has to be a RNA/DNA - code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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
code_get_acid(code, length = -1L)
```

#### Arguments
 
*code*	is either a string vector or a string. It should be a RNA/DNA - code or a sequence.<br>

*length*	if code is a sequence, length is the tuple length of the code.<br>


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

### genetic_codes_by_index

#### Usage
```R 
genetic_codes_by_index(idx, acid = "DNA")
```

#### Arguments
 
*idx*	the index of a Genetic Code table as int. (check *print_all_translation_table*)<br>

*a@param*	acid a String, is optional: DNA or RNA<br>


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
genetic_codes_by_name(name)
```

#### Arguments
 
*name*	the name of a Genetic Code as string. (check *print_all_translation_table*)<br>


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

### get_average_conductance_of_codeidx

#### Usage
```R 
get_average_conductance_of_codeidx(codeIdx, acid = "DNA")
```

#### Arguments
 
*codeIdx*	a Number, the index of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String, is optional: DNA or RNA<br>


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

### get_max_conductance_of_codeidx

#### Usage
```R 
get_max_conductance_of_codeidx(codeIdx, acid = "DNA")
```

#### Arguments
 
*codeIdx*	a Number, the index of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String, is optional: DNA or RNA<br>


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

### get_min_conductance_of_codeidx

#### Usage
```R 
get_min_conductance_of_codeidx(codeIdx, acid = "DNA")
```

#### Arguments
 
*codeIdx*	a Number, the index of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String, is optional: DNA or RNA<br>


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

### get_average_conductance_of_code

#### Usage
```R 
get_average_conductance_of_code(codeName, acid = "DNA")
```

#### Arguments
 
*codeName*	a String, the name of the genetic translation table. (see *print_all_translation_tables*)<br>

*acid*	a String, is optional: DNA or RNA<br>


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

*acid*	a String, is optional: DNA or RNA<br>


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

*acid*	a String, is optional: DNA or RNA<br>


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

### start_bda

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/codon_table.jpg?raw=true)

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
To add a BDA simply Call *add_bda*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
start_bda()
add_bda(1, 2, "C", "G", "A", "U")
add_bda(1, 3, "A", "G", "C", "U")
res <- run_bda_as_matrix()

```
<hr>

### code_start_bda

#### Usage
```R 
code_start_bda(code, length = -1L)
```

#### Arguments
 
*code*	is a DNA or RNA code as string vector.<br>


#### Return
 
Boolean value. True if the procedure has started


#### Description
 
Each added binary dichotomic algorithm (BDA) results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call *code_start_bda* or to start a procedure
for all RNA codons call *start_bda*.
To add a BDA simply Call *add_bda*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
code_start_bda(c("ACG", "CAG"))
add_bda(1, 2, "C", "G", "A", "T")
res.binary <- run_bda()

```
<hr>

### add_bda

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/bda_diagramm.png?raw=true)

#### Usage
```R 
add_bda(i_1, i_2, Q_11, Q_12, Q_21, Q_22)
```

#### Arguments
 
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
To add a BDA simply Call *add_bda*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
code_start_bda(c("ACG", "CAG"))
add_bda(1, 2, "C", "G", "A", "T")
res.binary <- run_bda()

```
<hr>

### run_bda

#### Usage
```R 
run_bda()
```

#### Arguments
 \-

#### Return
 
A List. A binary representation of the Code.


#### Description
 
This function executes the currently open binary dichotomic algorithm (BDA) procedure. Therefore, you need to start a BDA procedure.
You can call *code_start_bda* to start a procedure
for all codons call *start_bda*.
To add a BDA simply Call *add_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
code_start_bda(c("ACG", "CAG"))
add_bda(1, 2, "C", "G", "A", "T")
add_bda(1, 3, "A", "G", "C", "T")
res.binary <- run_bda()

```
<hr>

### run_bda_as_matrix

#### Usage
```R 
run_bda_as_matrix()
```

#### Arguments
 \-

#### Return
 
Binary results as Matrix. For example:<br> "UUU -> 00" "UCU -> 10" "UAU -> 00" "UGU -> 10" <br> "UUC -> 00" "UCC -> 10" "UAC -> 00" "UGC -> 10" <br>  "UUA -> 01" "UCA -> 11" "UAA -> 01" "UGA -> 11" <br>  "UUG -> 01" "UCG -> 11" "UAG -> 01" "UGG -> 11" <br>  "CUU -> 00" "CCU -> 00" "CAU -> 00" "CGU -> 00" <br>  "CUC -> 00" "CCC -> 00" "CAC -> 00" "CGC -> 00" <br>  "CUA -> 01" "CCA -> 01" "CAA -> 01" "CGA -> 01" <br>  "CUG -> 01" "CCG -> 01" "CAG -> 01" "CGG -> 01" <br>  "AUU -> 00" "ACU -> 10" "AAU -> 00" "AGU -> 10" <br>  "AUC -> 00" "ACC -> 10" "AAC -> 00" "AGC -> 10" <br>  "AUA -> 00" "ACA -> 10" "AAA -> 00" "AGA -> 10" <br>  "AUG -> 00" "ACG -> 10" "AAG -> 00" "AGG -> 10" <br>  "GUU -> 11" "GCU -> 11" "GAU -> 11" "GGU -> 11" <br>  "GUC -> 11" "GCC -> 11" "GAC -> 11" "GGC -> 11" <br>  "GUA -> 11" "GCA -> 11" "GAA -> 11" "GGA -> 11" <br>  "GUG -> 11" "GCG -> 11" "GAG -> 11" "GGG -> 11"


#### Description
 
This Function executes a binary dichotomic algorithm (BDA) procedure. It only works if the BDA procedure has been started by the *start_bda* function.
Each added binary BDA results one binary digit for each codon.
You can add multiple BDAs for one procedure. To add a rule, you need to start a BDA procedure first.
To do so you can either call *code_start_bda* or to start a procedure
for all RNA codons call *start_bda*.
To add a BDA simply Call *add_bda*. To execute the BDAs call *run_bda*.
A binary dichotomic algorithm generates a binary representation of a generic code. For more info on BDAs read:<br>
*M.Gumbel, E.Fimmel, A.Danielli, L.Struengmann. On Models of the Genetic  Code generated by Binary Dichotomic Algorithms*


#### Examples
```R 
start_bda()
add_bda(1, 2, "C", "G", "A", "U")
add_bda(1, 3, "A", "G", "C", "U")
res <- run_bda_as_matrix()

```
<hr>

<!--doc-end-->


# Copyright and license
Code and documentation copyright 2018-2019 Mannheim University of Applied Sciences. Code released under the GPL License, Version 2.0.
