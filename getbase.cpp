#include <QApplication>
#include <QWebView>
#include <QWebFrame>
#include <QDesktopWidget>
#include <QStandardPaths>
#include <QObject>
#include <QDesktopServices>


// Notre classe qu'on va passer au javascript par le Qt Bridge
class doSome: public QObject
{
	Q_OBJECT
public slots:

	// Un slot pour avoir l'adresse de la base de données
	Q_INVOKABLE QString getDataPath() {
	return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/data/getbase/getbase";
	}
	// Un slot pour ouvrir un lien vers l'article parlant de ce programme sur mon blog sur le navigateur par défaut
	Q_INVOKABLE void getLink() {
		QDesktopServices::openUrl(QUrl("http://dr-benltaief.blogspot.com/2015/02/dpm-base-sqlite-javascript-qtwebkit.html#up"));
	}
	// Un slot pour quitter l'application
	Q_INVOKABLE void closeApp() {
		QApplication::exit();
	return;
	}
};

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QWebView *view = new QWebView();

	// Un peu de déco..
	view->resize(800,170);
	view->setMinimumSize(800,170);
	view->setFixedSize(800,170);
	view->setWindowFlags(Qt::CustomizeWindowHint);
	view->setWindowFlags(Qt::FramelessWindowHint);
	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	int x = (screenGeometry.width()-800) / 2;
	int y = (screenGeometry.height()-170) / 2;
	view->move(x, y);

	view->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical,Qt::ScrollBarAlwaysOff);
	view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal,Qt::ScrollBarAlwaysOff);

	// Pas besoin de plugins.. :-)
	// view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);

	// Pas besoin de clic droit non plus n'est-ce pas? :-P
	view->setContextMenuPolicy(Qt::PreventContextMenu);

	// Besoin de Cross Scripting justement..
	view->settings()->setAttribute(QWebSettings::XSSAuditingEnabled,0);

	// ... et ça va de soi!
	view->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,1);

	// Un fix pour ne pas chercher la favicon
	QWebSettings::setIconDatabasePath("");

	// Besoin d'une base de données SQLite et de son adresse sur le disque.
	QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
	QWebSettings::globalSettings()->setOfflineStoragePath(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/data/getbase/getbase");
	// La taille maximale de notre base de données (ici 20Mo de requis)
	QWebSettings::setOfflineStorageDefaultQuota(20*1024*1024);

	// Besoin de déboguer?!
	// QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

	// On nettoie le cache du navigateur si jamais il en a gardé..
	QWebSettings::clearMemoryCaches();

	// Notre Qt Bridge vers notre classe doSome
	view->page()->mainFrame()->addToJavaScriptWindowObject(QString("doSome"), new doSome);

	// Le fichier index.html sur le disque au lieu de celui dans nos ressources?
	// view->load(QUrl(QUrl::fromUserInput(QApplication::applicationDirPath()).toString()+"/index.html"));

	view->load(QUrl("qrc:/index.html"));
	view->setWindowTitle("GetBase - Aspirateur de la base de données des médicaments de la DPM");
	view->show();

	return app.exec();
}
#include "getbase.moc"