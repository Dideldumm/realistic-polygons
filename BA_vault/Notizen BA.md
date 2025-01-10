# Letztes Meeting mit Prof. Schirra
- 3 Optionen 
	- Ergebnisse optimieren (durch draufgucken die Polygone klasssifizieren)
		- Punkte am rand zusätzlich generieren
	- Sklearn benutzen um die Polygone zu evaluieren
		- Realistische Testdaten von open street
		- Unrealistische durch CGAL generieren
	- Klassifikator für Polygone finden

## Ideen zur Definition / Beschreibung realistischer Polygone
--> siehe [[2-Opt_Moves_and_Flips_for_Area-optimal_Polygonizations]]

### Umfang minimieren
Eine Möglichkeit wäre Polygone aus der Punktmenge zu bilden, welche einen möglichst geringen Umfang haben.

1. Fläche minimal -> sieht doof aus
	- Min/max Fläche bildet keine schönen Polygone :C
	- ![[areaMinMaxPolygonizations.png]]
2. Umfang minimal -> Travelling Salesman Problem (TSP)

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
	- Wie mit gegebener Punkteanzahl umgehen
- Probleme:
	- Das Ergebnis ist relativ kreisförmig
	- -> Polygone verschieben, bevor sie vereinigt werden

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

