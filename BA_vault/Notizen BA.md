# Letztes Meeting mit Prof. Schirra
- Mehr Eigenschaften von Polygonen angucken und nach Bewertungsfunktionen schauen
- Thema konkretisieren
	- Eigenschaft raussuchen (aus Internet / [[Characterizations_of_real-world_Polygons.pdf]])
		- Könnte zum Beispiel _k-Link-Convexity_ sein (siehe [[Characterizations of real world Polygons#Characterizations of polygons]])
	- Algorithmus finden oder schreiben, der diese Eigenschaft an einem Polygon bewertet
	- Verschiedene Algorithmen zum Generieren vergleichen bezüglich der Eigenschaft
	- Die Eigenschaft  bewerten im Bezug darauf, wie realistisch das Polygon ist
- Zu jedem Algorithmus mal was aufschreiben
- Praktikumsbericht
	- Mehr Aufgaben, auch mal was komplexeres aufschreiben
	- Allgemein mehr, was ich gemacht habe und weniger über das Unternehmen
- _Vereinigung von konvexen Hüllen_
	- Punktemengen generieren:
		- Ruhig an der gleichen Stelle generieren
		- Jede Punktemenge um einen (zufälligen) Vektor verschieben
		- Jede Punktemenge (zufällig) skalieren
	- Mal ausprobieren, was bei disjunkten Polygonen passiert
		- Wie sieht `outer boundary` dann aus?
		- 2 _outer boundaries_?
		- Zur Not vermeiden durch gezieltes Verschieben der Punktemengen

# TODO
- Mit BA anfangen
	- Erstmal irgendwas hinschreiben
	- Die Gliederung und Themen ergeben sich dann schon
- Polygone lesen und schreiben
	- [CGAL - IO Streams](https://doc.cgal.org/latest/Stream_support/IOStreamSupportedFileFormats.html#IOStreamPLY)
		- Was ist Polygon Soup?
		- Einen Wrapper für IO schreiben?
	- Wavefront (`.obj`)
		- wird von Blender und [[2-Opt_Moves_and_Flips_for_Area-optimal_Polygonizations]] benutzt
		- Ist sehr mächtig und dementsprechend komplex
		- Wieviel nimmt CGAL ab?
	  - Polygon File Format (`.ply`)
		  - vermutlich weniger komplex als Wavefront
- TwoOpt implementation finden
	- [[2-Opt_Moves_and_Flips_for_Area-optimal_Polygonizations]]
- Notizen sortieren
	- Links zu Stellen in der BA hinzufügen
- Unit-Tests??

## Ideen zur Definition / Beschreibung realistischer Polygone
--> siehe [[2-Opt_Moves_and_Flips_for_Area-optimal_Polygonizations]]

### Umfang minimieren
Eine Möglichkeit wäre Polygone aus der Punktmenge zu bilden, welche einen möglichst geringen Umfang haben.

1. Umfang minimal -> Travelling Salesman Problem (TSP)
	- Es gibt viele Quellen für minimale / maximale Fläche, aber ich hab noch nix zu min/max Umfang gesehen
	- Min/max Fläche bildet keine schönen Polygone :C
	- ![[areaMinMaxPolygonizations.png]]

### Punkte Generieren
- Punkte nicht zufällig
	- Punkte nur in einem definierten Ring - skaliert nur das Problem :C
	

### Ziel / Zweck
realistische Polygone, sodass Tests von Algorithmen darauf sinnvolle Ergebnisse liefern
	- QuickHull ist im worst case quadratisch, aber das tritt im Praxisfall nicht auf 
	- QuickHull auf realistischen Polygonen sollte im worst case also nicht quadratisch sein

## Algorithmus - Ideen
- Delauney-Triangulierung und dann Kanten entfernen
	- welche Kanten?

### Umgesetzte Algorithmen
#### `MergeConvexHulls`
Pseudocode:
- Initiales Polygon ist die konvexe Hülle
- Bis alle Punkte zum Polygon gehören:
	- Neue konvexe Hülle bilden
	- Die Punkte der neuen konvexen Hülle zum Polygon hinzufügen
	- Jeder Punkt wird an der ihm nächstgelegenen Kante eingefügt

### Work In Progress

#### Union Of Convex Hulls
Ganz grob:
- Mehrere zufällige Punktmengen bilden
- Von jeder Punktmenge die konvexe Hülle bilden
- Die konvexen Hüllen vereinigen
	- [`CGAL::join(...)`](https://doc.cgal.org/latest/Boolean_set_operations_2/group__boolean__join.html)
- Zu klären: 
	- Wie genau die Punktmengen generieren
	  Generatoren von CGAL angucken
	- Wie mit gegebener Punkteanzahl umgeben
#### Merge Closest Chains
Mit Chain ist ein Polygonzug gemeint (also eine Kette von verbundenen Punkten)

Pseudocode
- Initialisiere jeden Punkt als Polygonzug 
- Füge die Polygonzüge einer Menge hinzu
- Bis nur noch ein einzelner Polygonzug in der Menge ist:
	- Suche die Polygonzüge, die sich am nächsten sind
	- Entferne die beiden Polygonzüge aus der Menge
	- Merge die beiden Polygonzüge
	- Füge den gemergten Polygonzug wieder zur Menge hinzu
- Bilde ein Polygon aus dem Polygonzug (nur End- und Anfangspunkt verbinden)

Probleme
- die letzte Kante (von End- zu Anfangspunkt des letzten Polygonzugs) hat fast immer viele Kreuzungen
- noch weitere Kreuzungen der anderen Kanten
- Was jetzt?
	- Two opt nutzen
	- Andere Funktion zum mergen überlegen

### Noch nicht genauer angeschaut
Idee Polygon ohne Überschneidungen abwandeln
	- rekursiver Algorithmus (divide and conquer)
	- leftmost und rightmost suchen
	- Punkte oberhalb und unterhalb der Linie zwischen leftmost/rightmost eigenen sets zuordnen
	- rekursiv anwenden, bis nur noch Linien vorhanden sind
	- linke Eckpunkte verbinden
	- rechte Eckpunkte verbinden
	- alle Mittellinien entfernen

### Verworfene Ideen
- Plane Sweep aber drehen 
	- -> star shaped polygons
	- Das resultierende polygon ist nicht wirklich realistisch

