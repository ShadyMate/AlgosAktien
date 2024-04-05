# AlgoDat-HashUebung-Protokoll:

## Datenstruktur:

Die implementierte Datenstruktur besteht aus zwei Hashtabellen zur Speicherung von Aktienobjekten.
Die Hashtabelle ist als Array von Zeigern auf Aktienobjekte implementiert.
Die Größe der Hashtabellen wird während der Initialisierung festgelegt und beträgt standardmäßig 1000.
Jedes Element in der Hashtabelle kann entweder auf ein Aktienobjekt verweisen oder den Wert nullptr haben,
um anzuzeigen, dass an dieser Position kein Objekt vorhanden ist.

## Hashfunktion und Kollisionserkennung:

Die Hashtabellen verwenden Hashfunktionen, um den Index für die Speicherung von Aktienobjekten zu berechnen.
Die verwendete Hashfunktion für die Namen ist eine einfache Summenfunktion, die die ASCII-Werte der Zeichen im Namen der Aktie addiert
und dann den Modulo-Operator verwendet, um den Index zu berechnen.
Die Acronym Hashfunktion ist sehr ähnlich und verwendet ebenfalls die ASCII-Werte des Acronyms um mittels Modulo einen Hash zu berechnen der im Bereich der 1000 Aktien liegt.
Diese Hashfunktion hat den Vorteil, dass sie einfach zu implementieren ist, jedoch Kollisionen begünstigen kann,
insbesondere wenn die Namen ähnliche Buchstabenhäufigkeiten aufweisen. Die quadratische Sondierung wird in der Funktion checkForCollision() verwendet, um nach freien Slots in der Hashtabelle zu suchen, wenn eine Kollision auftritt.

## Verwaltung der Kursdaten:

Die Kursdaten werden in einem separaten Vektor innerhalb jedes Aktienobjekts gespeichert.
Der Vektor enthält Objekte der Struktur StockVal, die das Datum sowie verschiedene Kurswerte wie Eröffnungskurs,
Schlusskurs usw. enthalten. Die Importfunktion importCSVData() liest Daten aus einer CSV-Datei ein und speichert sie in diesem Vektor.
Diese Struktur ermöglicht eine effiziente Verwaltung und den Zugriff auf die Kursdaten für jede Aktie.

## Löschalgorithmus:

Das Löschen eines Aktienobjekts aus der Hashtabelle erfolgt durch Suchen des Objekts anhand seines Namens mithilfe der Hashfunktion.
Wenn das Objekt gefunden wird, wird es gelöscht, und seine Referenz in der Hashtabelle wird auf nullptr gesetzt.
Zusätzlich wird das zugehörige Objekt aus der Akronym-Hashtabelle gelöscht. Dieser Löschalgorithmus hat eine
durchschnittliche Komplexität von O(1), da in den meisten Fällen nur eine einzelne Position in der Hashtabelle überprüft werden muss.

## Aufwandsabschätzung:

### Aufwand einer Hashtabelle normalerweise:
Einfügen: O(1), bei 1000 Aktien also 1000 Operationen | O(n)
Suchen: O(1), -.-
Löschen: O(1), -.-

### Aufwand eines Arrays:
Einfügen:
 - am Anfang: O(1)
 - beliebige Position: O(n), bei 1000 also bis zu 500.000 Operationen
Suchen: O(n), bei 1000 also bis zu 500.000 Operationen
Löschen:
O(n), bei 1000 also bis zu 500.000 Operationen

### Aufwand einer verketteten Liste:
Einfügen:
 - am Anfang: O(1)
 - beliebige Position: O(n), bei 1000 also bis zu 500.000 Operationen
Suchen: O(n), bei 1000 also bis zu 500.000 Operationen
Löschen: O(n), bei 1000 also bis zu 500.000 Operationen

### Schleifen:
Das Programm enthält keine expliziten Schleifen, die von der Größe der Eingabe abhängen.
Daher gibt es keine linearen oder quadratischen Iterationen.

### E/A-Operationen (cin, cout):
Die Laufzeitkomplexität von E/A-Operationen kann oft als konstant angenommen werden,
da sie nicht linear mit der Größe des Inputs skalieren.

### Rekursion:
Es gibt keine rekursiven Funktionen im Programm.

### Dynamische Speicherzuweisung:
Es gibt eine dynamische Speicherzuweisung im Hauptteil des Programms,
die jedoch nur einmal durchgeführt wird und nicht von der Größe des Inputs abhängt.

### Schlussfolgerung
Die Aufwandsabschätzung für die verschiedenen Operationen im Programm basiert auf der Komplexität der jeweiligen Operationen.
Die Hashtabelle bietet im Durchschnitt eine O(1)-Komplexität für das Einfügen, Löschen und Suchen von Elementen,
obwohl in seltenen Fällen eine O(n)-Komplexität auftreten kann, wenn viele Kollisionen auftreten und das lineare Sondieren
ineffizient wird. Die E/A-Operationen sowie die Verarbeitung der Kursdaten erfolgen in der Regel mit konstanter
Zeitkomplexität oder mit einer linearen Zeitkomplexität, die von der Anzahl der Kursdaten abhängt.
Daher liegt die Gesamtkomplexität des Programms in der Regel im Bereich von O(1) bis O(n),
wobei n die Anzahl der Elemente bzw. die Größe der Kursdaten ist.
