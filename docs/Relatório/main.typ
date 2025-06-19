#set document(
  title: "Relatório",
  author: "Gustavo Luciano, Jean Domingueti, Leonardo Verissimo, Rodrigo da Cruz, Silvio Estêvão",
  date: auto,
)
#set page(
    width: 21cm,
    height: 29.7cm,
    margin: (top: 3cm, bottom: 2cm, left: 3cm, right: 2cm),
)

#set par(
  justify: true,
  first-line-indent: (amount: 1em, all: true),
)

#set text(lang: "pt")
#include "componentes/capa.typ"
#pagebreak()
#set page(numbering: "1")
#include "componentes/sumario.typ"


#set heading(numbering: "1.1.")

#pagebreak()

#include "intro.typ"
#v(2em)
#include "organizacao.typ"
#v(2em)
#include "utilitarios.typ"
#v(2em)
#include "howtorun.typ"
#v(2em)
#include "estruturas.typ"
#v(2em)
#include "desafios.typ"
#v(2em)
#include "resultados.typ"
#v(2em)
#include "conclusao.typ"
#pagebreak()
#include "componentes/referencias.typ"
                                                                                          