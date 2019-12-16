

code <- "ACG CCG"
g<-GCATR::code_factor_graph(code)

for(l in names(V(g))) {
  print(l)
}