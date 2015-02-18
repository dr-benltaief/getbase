# GetBase - Aspirateur de la base de données des médicaments de la DPM

## À propos

Pour en savoir plus sur ce dépôt visitez [l'article sur mon blog](http://dr-benltaief.blogspot.com/2015/02/dpm-base-sqlite-javascript-qtwebkit.html#up).

## Compilation de l'application

> Vous aurez besoin de [Git](http://git-scm.com/downloads) et du [Framework Qt 5](http://www.qt.io/download-open-source/).

Faîtes un clone du dépôt:

```bash
git clone https//github.com/dr-benltaief/getbase
```

Dirigez-vous vers le dossier `getbase` et préparez le `Makefile` via `qmake`:

```bash
cd getbase
qmake 
```

Compilez via `make` (ou `mingw32-make` ou autre en fonction de votre système d'exploitation et de votre compilateur):

```bash
make
```

Sous Windows vous pouvez déployer l'application via:

```bash
windeployqt
```

et sous Mac vous pouvez la déployer via:

```bash
macdeployqt
```

## License

Ce code est livré comme tel sans aucune garantie ni aucun copyright. :wink: