# Particle Physics Simulation and K\* Reconstruction


#  Requisiti e installazione di ROOT

Il progetto usa **ROOT** per istogrammi, fit e I/O. Devi avere `root` e `root-config` nel `PATH`. Assicurarsi quindi che sia installato e perfettamente funzionante insieme a cmake. Attenzione per la compilazione potrebbe essere necessario installare ulteriori pacchetti.



2. **Analisi** (macro ROOT):

```bash
root -l -q analised.cpp
```

Se preferisci, puoi aprire ROOT e lanciare la funzione:

```bash
root -l
root [0] .x analised.cpp
```


#  Compilazione

Si usa CMake (file `CMakeLists.txt` incluso). Da root del progetto:

```bash
cmake -S . -B build
cmake --build build -j
```

Se CMake non trova ROOT, specifica il path:

```bash
cmake -S . -B build -DROOT_DIR=/percorso/alla/installazione/root
cmake --build build -j
```

L’eseguibile risultante è `build/particle_sim`.

---

#  Esecuzione

1. **Generazione degli istogrammi** (crea `histo.root`):

```bash
./build/particle_sim
```

## Overview

Questo progetto implementa una **simulazione Monte Carlo di eventi di fisica delle particelle** utilizzando ROOT per l’analisi statistica e la visualizzazione dei risultati.

L’obiettivo principale è:

>  **Ricostruire la risonanza K\*** (massa ~0.892 GeV) a partire dallo spettro delle masse invarianti delle coppie $\pi$–K.

Il codice simula eventi con produzione di particelle leggere ($\pi$, K, p) e di una risonanza instabile (K\*) che decade in due corpi. Successivamente analizza gli spettri di massa invariante per identificare il picco della risonanza sopra il fondo combinatoriale.

---

#  Struttura del Progetto

Il progetto è diviso in tre componenti principali:

## 1 `particle.cpp`

Implementa la classe `Particle`, che rappresenta una particella fisica con:

- nome
- quantità di moto (px, py, pz)
- massa
- carica
- eventuale larghezza di decadimento (per le risonanze)

### Funzionalità principali

- Calcolo dell’energia relativistica:
$$ E = \sqrt{p^2 + m^2}$$


- Calcolo della massa invariante tra due particelle:

$$m_{inv} = \sqrt{(E1 + E2)^2 - |p1 + p2|^2}$$


- Decadimento a due corpi (`Decay2Body`)
- Include effetto di larghezza della risonanza (Breit-Wigner simulato via distribuzione gaussiana)
- Genera i prodotti in modo isotropico
- Applica boost relativistico nel sistema del laboratorio

Questa classe è il cuore fisico del progetto.

---

## 2 `main.cpp`

È il **motore della simulazione**.

### Cosa fa

Definisce i tipi di particelle:
- $\pi$⁺, $\pi$⁻
- K⁺, K⁻
- p⁺, p⁻
- risonanza K\* (massa 0.89166 GeV, width 0.050 GeV)

Simula 100.000 eventi da 100 particelle

---

## Generazione delle particelle

Le particelle vengono generate con probabilità:

| Particella | Probabilità |
|------------|------------|
| $\pi$⁺ | 40% |
| $\pi$⁻ | 40% |
| K⁺ | 5% |
| K⁻ | 5% |
| p⁺ | 4.5% |
| p⁻ | 4.5% |
| K\* | 1% |

Il modulo della quantità di moto segue una distribuzione isotropa esponenziale:

$$p \sim e^{-p}$$
.

---

## Produzione e decadimento della K\*

Quando viene generata una risonanza:

1. Viene creata una particella `"resonance"`
2. Viene fatta decadere in:
   - $\pi$⁺ K⁻  (50%)
   - $\pi$⁻ K⁺  (50%)

3. Si registra:
   - massa invariante dei prodotti di decadimento
   - contributo al fondo combinatoriale

Questo è fondamentale per verificare che il picco della risonanza sia ricostruibile anche in presenza di fondo.

---
#  Analisi (`analised.cpp`)

La fase di analisi legge il file ROOT generato e verifica la coerenza fisica e statistica della simulazione.

---

## Controlli di consistenza

- Numero totale di particelle generate  
- Distribuzione delle specie ($\pi$, K, p, K\*)  
- Confronto con le probabilità teoriche (compatibilità entro $3\sigma$)

L’obiettivo è verificare che la generazione Monte Carlo riproduca correttamente le frazioni impostate nel generatore.

---

## Studio delle distribuzioni

Vengono analizzate diverse osservabili cinematiche:

- Distribuzione uniforme degli angoli ($\phi$, $\theta$)
- Fit esponenziale del modulo della quantità di moto:

$$ f(p) \propto e^{-p} $$

- Spettri di massa invariante costruiti per:
  - tutte le coppie
  - coppie a stessa carica
  - coppie a carica opposta
  - sole coppie $\pi$–K

---

## Sottrazione del fondo combinatoriale

Per isolare il segnale della K\* si utilizza la differenza tra coppie a carica opposta e coppie a stessa carica:

$$
\text{Signal}(m) =
\left( \frac{dN}{dm} \right)_{\text{opposite charge}}
-
\left( \frac{dN}{dm} \right)_{\text{same charge}}
$$

Questo metodo riduce il fondo non correlato, lasciando emergere il contributo delle vere risonanze.

Si ottengono due spettri:

- Spettro completo (tutte le combinazioni)
- Spettro selezionando solo coppie $\pi$–K (fisicamente più pulito)

---

##  Fit della risonanza

Il picco viene fittato con una funzione gaussiana:

$$
f(m) = A \exp\left(
-\frac{(m - \mu)^2}{2\sigma^2}
\right)
$$

Dal fit si estraggono:

- Massa della K\* ($\mu$)
- Larghezza osservata ($\sigma$)
- $\chi^2/\text{NDF}$
- Probabilità del fit

Il risultato atteso è una massa compatibile con:

$$
m_{K^*} \approx 0.892 \ \text{GeV}
$$

---

# Perché questo progetto è interessante

Questo codice riproduce in forma semplificata tecniche reali di analisi in fisica delle alte energie:

- Ricostruzione di risonanze tramite massa invariante  
- Stima e sottrazione del fondo combinatoriale  
- Fit statistici con ROOT  
- Validazione tramite $\chi^2$ e probabilità del fit  

Per farlo si passa attraverso tutte le fasi partendo dalla simulazione in cui vengono generate le particelle secondo una data distribuzione e si studia il decadimento delle possibili $k^*$ all'analisi dei dati nella quale si costruiscono gli istogrammi delle possibili combinazioni per poi rimuovere il fondo. Questo processo permette quindi di evidenziare un picco nel grafico della massa invariante evidenziando così la presenza della risonanza.

Lo scopo fisico è dimostrare che una risonanza instabile può essere identificata attraverso le sue particelle di decadimento anche in presenza di un grande fondo statistico.

---
