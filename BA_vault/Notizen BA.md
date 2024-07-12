# Fragen an Schirra und Tetjana
- maximale Laufzeit zum Generieren eines Polygons?
- 


## Ideen für "realistische" Polygone

--> siehe [[2-Opt_Moves_and_Flips_for_Area-optimal_Polygonizations]]

Am Ende suchen wir sicherlich das Polygon welches den geringsten Umfang aller möglichen Polygone aus der Punktemenge hat. (na vielleicht auch nicht, aber die Idee will ich gerne nicht wegschmeißen)

1. Umfang minimal -> Travelling Salesman Problem (TSP)
	- Es gibt viele Quellen für minimale / maximale Fläche, aber ich hab noch nix zu min/max Umfang gesehen
	- Min/max Fläche bildet keine schönen Polygone :C
	- ![[areaMinMaxPolygonizations.png]]
2. [Fatness](https://en.wikipedia.org/wiki/Fat_object_(geometry)) minimal


- Punkte nicht zufällig
	- Punkte nur in einem definierten Ring
- Two Opt: Heuristik für TSP 
- Systematisch Ausprobieren
	- Vor und Nachteile
- Früh mit schreiben anfangen 
	- Motivation 
	- Was gibt es schon
- Github durchsuchen
- CG:Shop
- Auer und Held Paper
- Polygonalisierung
	- Wie viele Punkte kann man für eine gegebene Punktemenge finden
- realistische Polygone, sodass Tests von Algorithmen darauf sinnvolle Ergebnisse liefern
	- QuickHull ist im worst case quadratisch, aber das tritt im Praxisfall nicht auf 
	- QuickHull auf realistischen Polygonen sollte im worst case also nicht quadratisch sein


## Ideen für Algorithmen

- Delauney-Triangulierung und dann Kanten entfernen
	- welche Kanten?
- Konvexe Hülle bilden
	- Punkt, der am nächsten an einer Kante ist, an dieser Kante hinzufügen
	- Wiederholen bis alle Punkte zum Polygon dazugehören
-  Konvex Layer
       - Konvexe Hülle bilden
	- Von den übrigen Punkten die Konvexe Hülle bilden
	- Bis alle Punkte zu einer konvexen Hülle gehören
	- Die Hüllen irgendwie mergen
- Plane Sweep aber drehen?
	- Funktioniert glaube nicht so gut
- Idee Polygon ohne Überschneidungen abwandeln
	- rekursiver Algorithmus (divide and conquer)
	- leftmost und rightmost suchen
	- Punkte oberhalb und unterhalb der Linie zwischen leftmost/rightmost eigenen sets zuordnen
	- rekursiv anwenden, bis nur noch Linien vorhanden sind
	- linke Eckpunkte verbinden
	- rechte Eckpunkte verbinden
	- alle Mittellinien entfernen
