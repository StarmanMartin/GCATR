
# Version 0.1 is only a beta and not ready for use.

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/logo.png?raw=true)

This project contains the source code for R version of the Genetic Code Analysis Toolkit (GCAT) project. Please refer to the [public homepage](http://www.gcat.bio/) and the [project homepage](http://www.mbi.hs-mannheim.de/research/mathematics-of-the-genetic-information.html) for more information.

# Installation
GCATR is available for R version 3.5 and higher. It requires a C++11 (or later) compiler and [Rcpp (>= 0.12.18)](https://cran.r-project.org/web/packages/Rcpp/index.html) installed on your machine. 
Furthermore the current version of devtools needs to be installed on your computer. Install the R package by:
 * starting the a R console and run:
   ```R
   install.packages("devtools")
   devtools::install_github("StarmanMartin/GCATR")
   ```

 
# Components


## Codes

### get_rna_codon_list

This function makes a List of all RNA codon. It will generate the following list:<br/>
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
Returns the tables displayed in the table above. The tables will be stored in a matrix object. 

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

![Genetic Code Analysis Toolkit Logo](/man/resources/bio/gcat/bda_diagramm.pdf?raw=true)<br/><br/>

## Analysis Tool

# Copyright and license
Code and documentation copyright 2018-2019 Mannheim University of Applied Sciences. Code released under the GPL License, Version 2.0.
