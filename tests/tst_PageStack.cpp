#include <QCoreApplication>
#include <QSignalSpy>
#include <QTest>
#include "components/containers/PageStack.h"

using namespace FlatGui::Components::Containers;

class PageStackTest : public QObject
{
	Q_OBJECT
public:
	PageStackTest();
	~PageStackTest();

private:
	PageStack *_pageStack;

private slots:
	void initTestCase();
	void init();
	void cleanupTestCase();
	void cleanup();
	void test_freshPageStack();
	void test_addNewPage();
	void test_addSamePage();
	void test_addNullPage();
	void test_setCurrentIndex();
	void test_setSameCurrentIndex();
	void test_setInvalidCurrentIndex();
	void test_insertPageBeforeCurrent();
	void test_insertPageAfterCurrent();
	void test_deletePage();
};

PageStackTest::PageStackTest() :
	_pageStack{nullptr}
{

}

PageStackTest::~PageStackTest()
{

}

void PageStackTest::initTestCase()
{

}

void PageStackTest::init()
{
	_pageStack = new PageStack();
}

void PageStackTest::cleanupTestCase()
{

}

void PageStackTest::cleanup()
{
	_pageStack->deleteLater();
}

void PageStackTest::test_freshPageStack()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);

	QCOMPARE(_pageStack->pageCount(), 0);
	QCOMPARE(_pageStack->currentIndex(), -1);
	QCOMPARE(_pageStack->currentPage(), nullptr);
	QCOMPARE(spyPageCountChanged.count(), 0);
	QCOMPARE(spyCurrentPageChanged.count(), 0);
}

void PageStackTest::test_addNewPage()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);

	_pageStack->addPage(new QWidget());

	QCOMPARE(_pageStack->pageCount(), 1);
	QCOMPARE(_pageStack->currentIndex(), -1);
	QCOMPARE(_pageStack->currentPage(), nullptr);
	QCOMPARE(spyPageCountChanged.count(), 1);
	QCOMPARE(spyCurrentPageChanged.count(), 0);
}

void PageStackTest::test_addSamePage()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);
	auto *page{new QWidget()};

	_pageStack->addPage(page);
	_pageStack->addPage(page);

	QCOMPARE(_pageStack->pageCount(), 1);
	QCOMPARE(_pageStack->currentIndex(), -1);
	QCOMPARE(_pageStack->currentPage(), nullptr);
	QCOMPARE(spyPageCountChanged.count(), 1);
	QCOMPARE(spyCurrentPageChanged.count(), 0);
}

void PageStackTest::test_addNullPage()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);

	_pageStack->addPage(nullptr);

	QCOMPARE(_pageStack->pageCount(), 0);
	QCOMPARE(_pageStack->currentIndex(), -1);
	QCOMPARE(_pageStack->currentPage(), nullptr);
	QCOMPARE(spyPageCountChanged.count(), 0);
	QCOMPARE(spyCurrentPageChanged.count(), 0);
}

void PageStackTest::test_setCurrentIndex()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);
	auto *page{new QWidget()};

	_pageStack->addPage(page);
	_pageStack->setCurrentIndex(0);

	QCOMPARE(_pageStack->pageCount(), 1);
	QCOMPARE(_pageStack->currentIndex(), 0);
	QCOMPARE(_pageStack->currentPage(), page);
	QCOMPARE(spyPageCountChanged.count(), 1);
	QCOMPARE(spyCurrentPageChanged.count(), 1);
}

void PageStackTest::test_setSameCurrentIndex()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);
	auto *page{new QWidget()};

	_pageStack->addPage(page);
	_pageStack->setCurrentIndex(0);
	_pageStack->setCurrentIndex(0);

	QCOMPARE(_pageStack->pageCount(), 1);
	QCOMPARE(_pageStack->currentIndex(), 0);
	QCOMPARE(_pageStack->currentPage(), page);
	QCOMPARE(spyPageCountChanged.count(), 1);
	QCOMPARE(spyCurrentPageChanged.count(), 1);
}

void PageStackTest::test_setInvalidCurrentIndex()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);
	auto *page{new QWidget()};

	_pageStack->addPage(page);
	_pageStack->setCurrentIndex(1);
	_pageStack->setCurrentIndex(-2);

	QCOMPARE(_pageStack->pageCount(), 1);
	QCOMPARE(_pageStack->currentIndex(), -1);
	QCOMPARE(_pageStack->currentPage(), nullptr);
	QCOMPARE(spyPageCountChanged.count(), 1);
	QCOMPARE(spyCurrentPageChanged.count(), 0);
}

void PageStackTest::test_insertPageBeforeCurrent()
{
	QSignalSpy spyPageCountChanged(_pageStack, &PageStack::pageCountChanged);
	QSignalSpy spyCurrentPageChanged(_pageStack, &PageStack::currentPageChanged);
	auto *page1{new QWidget()};
	auto *page2{new QWidget()};
	auto *page3{new QWidget()};

	_pageStack->addPage(page1);
	_pageStack->addPage(page2);
	_pageStack->addPage(page3);
	_pageStack->setCurrentIndex(1);
	// _pageStack.insertPage();

	QCOMPARE(_pageStack->pageCount(), 1);
	QCOMPARE(_pageStack->currentIndex(), -1);
	QCOMPARE(_pageStack->currentPage(), nullptr);
	QCOMPARE(spyPageCountChanged.count(), 1);
	QCOMPARE(spyCurrentPageChanged.count(), 0);
}

void PageStackTest::test_insertPageAfterCurrent()
{

}

void PageStackTest::test_deletePage()
{

}

QTEST_MAIN(PageStackTest)

#include "tst_PageStack.moc"
