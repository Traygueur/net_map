# Net_map

## Sommaire
- [🗺️ Présentation](#présentation)
- [🛠️ Fonctionnalités principales](#fonctionnalités-principales)
- [📦 Structure du projet](#structure-du-projet)
- [⚙️ Pré-requis (développement)](#pré-requis-développement)
- [✅ Utilisation](#utilisation)
- [🧠 Notes complémentaires](#notes-complémentaires)
- [📄 Exemple de format JSON attendu](#exemple-de-format-json-attendu)
- [✍️ Auteur](#auteur)


## Présentation :
**Net_map** est une application Qt développée en C++ permettant de visualiser les résultats de scans réseau réalisés via Nmap, en mettant en évidence les ports détectés, leurs protocoles, leur état, ainsi qu'un indice de dangerosité basé sur une base de données locale au format JSON.

## Fonctionnalités principales

- 🗺️ Cartographie de réseaux
- Ouverture et parsing de fichiers XML générés par Nmap
- Affichage des hôtes et des ports détectés dans une interface graphique
- Attribution d’un score de dangerosité (de 0 à 5) pour chaque port détecté


## Structure du projet

```
Net_map/
├── json_data/
│   └── ports_info.json      # Base de données des ports et niveaux de danger
├── libs/
│   └── nlohmann/            # Librairie : Gestion de json en C++
├── main.cpp                 # Point d’entrée de l’application
├── mainwindow.ui            # Interface graphique (Qt Designer)
├── mainwindow.cpp/.h        # Logique de l’interface principale (GUI)
├── map.cpp/.h               # Parsing et traitement des données Nmap, Création de la cartographie
├── portsinfo.cpp/.h         # Chargement des données JSON des ports
├── scan.cpp/.h         # Gestion et lancement des scannes nmap
└── globals.h                # Variables globales (ex : chemin d’exécution)
```

## Pré-requis (développement)

- Qt 6.8 avec les modules `GUI`, `Widgets`, `Xml`, et `Svg`
- Visual Studio (Pour utiliser `.vcxproj`)

## Utilisation

### Depuis Visual Studio :
1. Compiler l’application depuis Visual Studio.
### Depuis le dossier du logiciel (portable) :
1. Exécuter le fichier exe de l’application depuis le dossier du logiciel.

### Une fois le logiciel lancé :
2. Au lancement, l’application charge automatiquement la base de ports JSON.
3. Utilisez le bouton "Scanner le réseau" pour lancer un scan en renseignant un sous-réseau, ou le bouton d’import (menu NetMap) pour sélectionner un fichier `.xml` généré par Nmap.
4. La cartographie se génère à la fin du scan, et les données seront affichées dans un tableau (informations sur les périphériques et de sécurité).

## Notes complémentaires

- Le fichier JSON contient les informations sur les ports : numéro, protocole de base, dangerosité.

## Exemple de format attendu (ports_info.json)

```json
{
    "7": {
        "protocol": "echo",
        "danger_level": 3
    },
    "22": {
        "protocol": "ssh",
        "danger_level": 3
    },
    "13": {
        "protocol": "daytime",
        "danger_level": 1
    },
}
```

## Auteur

Projet réalisé par Jérémy Coulombel, Mattéo Durand, Noan Hubert, Louis Porterie (cadre : projet scolaire en réseau et cybersécurité).
