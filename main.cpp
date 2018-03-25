#include "LSystemProject.h"
#include <QtWidgets/QApplication>
//
//#include "GeometricAction.h"
#include "qregexp.h"
#include <iostream>
#include <fstream>
#include "NPNExpressionParser.h"
#include "ProductionParser.h"
#include <thread>

//
//#define M2(a,b) (a+b)
//#define M1(a, p1,p2) M2 p1 + M2 p2
//
//
//#define FIRST(_a, _b) _a
//#define SECOND(_a, _b) _b

//int main__() {
//	ProductionParser parser{new NPNExpressionParser<param_t>};
//	auto p = parser.parse("Q{a;b} -> A{+ a 1; b} Q{- a 1; * b 2}");
//	float f = QString{"  3.01 "}.toFloat();
//	return 0;
//}

void draw(QPainter* painter, int n, int x, int y) {
	repeat(n)
		painter->drawLine(x::random<int>(0,x), 
						  x::random<int>(0,y),
						  x::random<int>(0,x),
						  x::random<int>(0,y));
}

void rep(volatile bool* v) {
	while (*v) { Sleep(1); }
}


#include "ThreadPool.h"

class J: public Job
{
public:
	QPainter* painter;
	int n;

	J(QPainter* p, int n):
		painter(p),
		n(n)
	{ }

	virtual void execute() override {
		repeat(n)
			painter->drawLine(x::random<int>(0,4000), 
							  x::random<int>(0,4000),
							  x::random<int>(0,4000),
							  x::random<int>(0,4000));
	}
};


int mainn(int argc, char** argv) {
	int sx = 100;
	int sy = 100;
	int n = 100000;
	int nt = 5;
	volatile bool v = true;

	QApplication a(argc, argv);
	QPixmap *image = new QPixmap(sx, sy);
	QPainter* painter = new QPainter(image);
	painter->drawLine(0, 0, 100, 100);
	painter->end();
	QPixmap* sim = new QPixmap(1000, 1000);
	painter->begin(sim);
	painter->setTransform(QTransform{}.scale(10, 10));
	painter->drawPixmap(0, 0, *image);
	painter->end();


	//ThreadPool pool(nt);
	//pool.run();
	//std::cin.get();
	//x::tic();
	//x::vector<Job*> jobs(nt);
	//for (int i = 0; i<nt; ++i)
	//	jobs.push_back(new J{painter, n/nt});
	////std::cout << x::toc() << std::endl;
	//pool.setJobs(jobs);
	////x::tic();
	//pool.finish();

	///*x::vector<std::thread> threads(nt);
	//threads.initialize_construct(draw, painter, n/nt, sx-1, sy-1);
	//threads.initialize_construct(rep, &v);
	//threads.call(&std::thread::join);*/
	//std::cout << x::toc() << std::endl;
	sim->save("D:\\temp\\test\\scaled_pixmap.bmp");
	return 0;
}


int main_0() {
	Var v(0);
	QVariant qv(0);

	x::tic();
	repeat(100000) {
		QString s{std::to_string(v.as<int>()).data()};
	}
	std::cout<<x::toc()<<std::endl;

	x::tic();
	repeat(100000) {
		QString s = qv.toString();
	}
	std::cout<<x::toc()<<std::endl;

	x::tic();
	repeat(100000) {
		int i = v.as<int>();
	}
	std::cout<<x::toc()<<std::endl;

	x::tic();
	repeat(100000) {
		int i = qv.toInt();
	}
	std::cout<<x::toc()<<std::endl;

	return 0;
}

int main(int argc, char *argv[])
{
	/*QVariant v;

	Setting s{"n", QVariant::Invalid};

	v = "1";
	v.toInt();
	return 0;*/

	//QApplication app(argc, argv);
	//SettingsManager man;
	//man.insert("s0", 1);
	//man.insert("s1", 0.001f);
	//man.insert("s2", QString("also"));
	//SettingsWidget sw(&man);
	//sw.show();
	//return app.exec();

	//using std::cout;
	//using std::endl;


	////QRegExp r{"([a-z])\s*\(\s*([a-z]),"}
	///*QRegExp r1{"(\\S)\\s*(\\(.*)\\))?\\s*->\\s*(.+)"};*/
	//QRegExp line{"(\\S)\\s*(?:\\{(.*)\\})?\\s*->(.+)"};
	//QRegExp predArg{"([a-z])(?:\\s*,\\s*)?"};
	//QRegExp succSymbol{"(\\S)\\s*(?:\\{([^}]*)\\})?\\s*"};
	////succSymbol.setMinimal(true);
	////r1.indexIn("Q (a,b) -> sth");
	//line.exactMatch("Q {  a,b, c}->A{a+ 1} B {sin(a+b) }");
	//QString pred = line.cap(1);
	//QString args = line.cap(2);
	//QString succ = line.cap(3);

	//cout<<pred.toStdString()<<endl;
	//cout<<args.toStdString()<<endl;
	//cout<<succ.toStdString()<<endl;

	//int pos = 0;
	//while ((pos = predArg.indexIn(args, pos)) != -1) {
	//	cout<<predArg.cap(1).toStdString()<<endl;
	//	pos += predArg.matchedLength();
	//	cout<<"pos: "<<pos<<endl;
	//}
	//cout<<"pos: "<<pos<<endl;

	//pos = 0;
	//while ((pos = succSymbol.indexIn(succ, pos)) != -1) {
	//	cout<<succSymbol.cap(1).toStdString()<<endl;
	//	cout<<succSymbol.cap(2).toStdString()<<endl;
	//	pos += succSymbol.matchedLength();
	//	cout<<"pos: "<<pos<<endl;
	//}
	//cout<<"pos: "<<pos<<endl;

	//cout<<r1.cap(1).toStdString()<<endl;
	//cout<<r1.cap(2).toStdString()<<endl;
	//cout<<r1.cap(3).toStdString()<<endl;

	/*bool b = r.exactMatch("abcd");*/
	//int pos = 0;
	//while ((pos = r.indexIn("a, b ,  c)", pos)) != -1) {
	//	cout<<r.cap(1).toStdString();
	//	pos += r.matchedLength();
	//}
	////cout<<b;
	////if (pos > -1) {
	//	for (int i = 0; i<=4; ++i)
	//		 cout<<endl<<r.cap(i).toStdString();
	//}

	/*NPNExpressionParser<float> parser;
	auto e = parser.parse("+ a * 2 - a 1");
	cout<<(*e)(20.f)<<endl;*/


	//for (auto i :{APPLY_CONCAT_C(FIRST, (6,2), (51,0), (9,0))})
	//	std::cout<<i;

	/*std::ofstream file("D:\\temp\\test\\apply_concat_c.h");

	for (int i = 1; i<=100; ++i) {
		file<<"#define __APPLY_CONCAT_C_"<<i<<"(_m";
		for (int k = 0; k<i; ++k)
			file<<", _a"<<k;
		file<<") _m _a0";
		for (int k = 1; k<i; ++k)
			file<<", _m _a"<<k;
		file<<"\n";
	}*/

//	return 0;
	QApplication a(argc, argv);
	LSystemProject w;
	w.show();
	return a.exec();
}
