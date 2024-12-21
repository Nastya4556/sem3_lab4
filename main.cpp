#include <QApplication>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <string>
#include <QFileDialog>
#include <QString>
#include <QComboBox>
#include <QInputDialog>
#include <QMessageBox>

#include "UndirectedGraph.h"


QWidget* createMainPage(QStackedWidget *stackedWidget) {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    QLabel *label = new QLabel;
    label->setText("<font color = 'darkCyan', span style = 'font-size: 20px;'>Finding the smallest path between verticles</font>");
    label->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label);
    QPushButton *buttonToPage2 = new QPushButton("Start", page);
    buttonToPage2->setStyleSheet("color: darkCyan; background-color: darkGray");
    layout->addWidget(label);
    layout->addWidget(buttonToPage2);
    page->setLayout(layout);
    QObject::connect(buttonToPage2, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    return page;
}

class Circle {
public:
    QPoint center;
    int index;
    Circle(const QPoint &c, int i) : center(c), index(i) {}
};

class Connection {
public:
    int index1;
    int index2;
    int weight;
    Connection(int i1, int i2, int w) : index1(i1), index2(i2), weight(w) {}
};

class GraphView : public QGraphicsView {
Q_OBJECT
public:
    GraphView(QWidget *parent = nullptr);
    ~GraphView();
    UndirectedGraph<int, int> getGraph();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QList<Circle> circles;
    QList<Connection> connections;
    QLabel *label;
    UndirectedGraph<int, int> graph;
    QPoint lastPoint;
    QRect drawArea;
    void connectCircles(int index1, int index2, int weight);
    bool isInDrawArea(const QPoint &point);
};

GraphView::GraphView(QWidget *parent) : QGraphicsView(parent) {
    setGeometry(100, 100, 800, 600);
    label = new QLabel("Draw Graph");
    label->setAlignment(Qt::AlignHCenter);
    int parentWidth = this->width();
    int labelWidth = label->width();
    int x = (parentWidth - labelWidth) / 2;
    label->setStyleSheet("font-size: 14px; color:black");
    label->setGeometry(600, 800, 150, label->height());
    drawArea = QRect(0, 0, 900, 600);
}

GraphView::~GraphView() {
}

void GraphView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isInDrawArea(event->pos())) {
        int index = circles.size() + 1;
        circles.append(Circle(event->pos(), index));
        update();
    } else if (event->button() == Qt::RightButton && isInDrawArea(event->pos())) {
        bool ok;
        int firstIndex = QInputDialog::getInt(this, "Connect vertices", "Select first verticle index:", 1, 1, circles.size(), 1, &ok);
        if (ok) {
            int secondIndex = QInputDialog::getInt(this, "Connect vertices", "Select second verticle index:", 1, 1, circles.size(), 1, &ok);
            if (ok && firstIndex != secondIndex) {
                int weight = QInputDialog::getInt(this, "Arc Weight", "Enter arc weight:", 1, 1);
                connectCircles(firstIndex - 1, secondIndex - 1, weight);
            }
        }
        update();
    }
}

void GraphView::connectCircles(int index1, int index2, int weight) {
    if (index1 >= 0 && index1 < circles.size() && index2 >= 0 && index2 < circles.size()) {
        connections.append(Connection(index1, index2, weight));
        graph.addEdge(circles[index1].index, circles[index2].index, weight); // Добавляем ребро в граф
    }
}

bool GraphView::isInDrawArea(const QPoint &point) {
    return drawArea.contains(point);
}

void GraphView::paintEvent(QPaintEvent *event) {
    QPainter painter(viewport());
    painter.setBrush(Qt::darkGray);
    painter.setPen(Qt::black);
    for (const Circle &circle : circles) {
        painter.drawEllipse(circle.center.x() - 20, circle.center.y() - 20, 40, 40);
        painter.drawText(circle.center.x() - 10, circle.center.y() + 5, QString::number(circle.index));
    }
    painter.setPen(Qt::black);
    for (const auto &connection : connections) {
        const Circle &circle1 = circles[connection.index1];
        const Circle &circle2 = circles[connection.index2];
        painter.drawLine(circle1.center, circle2.center);
        QPoint midPoint((circle1.center.x() + circle2.center.x()) / 2, (circle1.center.y() + circle2.center.y()) / 2);
        painter.drawText(midPoint.x(), midPoint.y(), QString::number(connection.weight));
    }
    painter.setPen(Qt::gray);
}
UndirectedGraph<int, int> GraphView::getGraph() {
    return graph;
}


QWidget* createPage3(QStackedWidget *stackedWidget) {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    QLabel *label1 = new QLabel;
    label1->setText("<font color = 'darkCyan', span style = 'font-size: 20px;'>Draw Graph</font>");

    label1->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label1);
    GraphView *graphView = new GraphView(page);
    graphView->setMinimumSize(600, 400);
    layout->addWidget(graphView);
    QPushButton *buttonBack = new QPushButton("Go home", page);
    buttonBack->setStyleSheet("color: darkCyan; background-color: darkGray");

    QLabel *label2 = new QLabel;
    label2->setText("<font color = 'darkCyan', span style = 'font-size: 15px;'>Finding shortest path between</font>");
    label2->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label2);

    page->setLayout(layout);
    QObject::connect(buttonBack, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    QHBoxLayout *inputLayout = new QHBoxLayout;
    QLineEdit *startEdit = new QLineEdit(page);
    startEdit->setPlaceholderText("Start vertex");
    QLineEdit *endEdit = new QLineEdit(page);
    endEdit->setPlaceholderText("End vertex");
    inputLayout->addWidget(startEdit);
    inputLayout->addWidget(endEdit);
    layout->addLayout(inputLayout);
    QPushButton *findPathButton = new QPushButton("Find Shortest Path", page);
    findPathButton->setStyleSheet("color: darkCyan; background-color: darkGray");
    layout->addWidget(findPathButton);
    layout->addWidget(buttonBack);
    QObject::connect(findPathButton, &QPushButton::clicked, [=]() {
        bool ok1, ok2;
        int startVertex = startEdit->text().toInt(&ok1);
        int endVertex = endEdit->text().toInt(&ok2);
        UndirectedGraph<int, int> graph = graphView->getGraph();
        if (ok1 && ok2 && graph.getSize() != 0) {
            std::cout << "Start vertex: " << startVertex << std::endl;
            std::cout << "End vertex: " << endVertex << std::endl;
            Path<int> shortestPath = graph.dijkstraPath(startVertex, endVertex);
            for (int i = 0; i < shortestPath.getSize(); i++)
            {
                std::cout << shortestPath.get(i) << " ";
            }
            std::cout << std::endl;
            std::string pathString = "Shortest path between " + std::to_string(startVertex) + " and " + std::to_string(endVertex) + " : " + std::to_string(shortestPath.get(0));
            for (int i = 1; i < shortestPath.getSize(); i++) {
                pathString += " -> " + std::to_string(shortestPath.get(i));
            }
            std::string message = "Shortest path";
            QMessageBox::information(page, message.c_str() , pathString.c_str());
            //QMessageBox::information(page, "Shortest Path", "Shortest path found!");
        } else {
            QMessageBox::warning(page, "Invalid Input", "There is no path between the vertices or the vertices themselves. Please try again.");
        }
    });
    return page;
}



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *mainWindow = new QWidget;
    QStackedWidget *stackedWidget = new QStackedWidget(mainWindow);
    stackedWidget->addWidget(createMainPage(stackedWidget));
    stackedWidget->addWidget(createPage3(stackedWidget));

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWindow);
    mainLayout->addWidget(stackedWidget);

    mainWindow->setLayout(mainLayout);
    mainWindow->resize(935, 500);
    mainWindow->setWindowTitle("Finding the smallest path between verticles");
    mainWindow->setStyleSheet("background-color: lightGray");
    mainWindow->show();

    return app.exec();
}
#include "main.moc"
