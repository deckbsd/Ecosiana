// EcosianaConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "EcosiaWebSearcher.h"
#include "EcosiaVideoSearcher.h"

void test_simple()
{
	EcosiaWebSearcher searcher;
	list<EcosiaWebResult> results;

	results = searcher.simple_web_research("simple test");

	for (list<EcosiaWebResult>::iterator s = results.begin(); s != results.end(); s++)
	{
		std::cout << "TITLE :";
		std::cout << s->title_raw << endl;
		std::cout << "TITLE CLEARED :";
		std::cout << s->title_cleared() << endl;
		std::cout << "URL :";
		std::cout << s->url_raw << endl;
		std::cout << "DESCRIPTION :";
		std::cout << s->description_raw << endl;
		std::cout << "CLEARED DESCRIPTION :";
		std::cout << s->description_cleared() << endl;
	}

}


void test()
{
	ecosia_web_parameters params;
	EcosiaWebSearcher searcher;
	list<EcosiaWebResult> results;

	params.language = "fr";
	params.page = 2;
	params.region = "be";

	results = searcher.web_research("simple test", params);

	for (list<EcosiaWebResult>::iterator s = results.begin(); s != results.end(); s++)
	{
		std::cout << "TITLE :";
		std::cout << s->title_raw << endl;
		std::cout << "TITLE CLEARED :";
		std::cout << s->title_cleared() << endl;
		std::cout << "URL :";
		std::cout << s->url_raw << endl;
		std::cout << "DESCRIPTION :";
		std::cout << s->description_raw << endl;
		std::cout << "CLEARED DESCRIPTION :";
		std::cout << s->description_cleared() << endl;
	}

	results = searcher.web_research("simple test 2", params);

	int i = searcher.get_total_searches();

	cout << endl << "total searches : " + i << endl;

}

void test_video()
{
	ecosia_video_parameters params;
	EcosiaVideoSearcher searcher;
	list<EcosiaVideoResult> results;

	params.resolution = "all";
	params.page = 1;
	params.video_length = "short";
	params.pricing = "paid";

	results = searcher.video_research("simple test", params);

	for (list<EcosiaVideoResult>::iterator s = results.begin(); s != results.end(); s++)
	{
		std::cout << "TITLE :";
		std::cout << s->title_raw << endl;
		std::cout << "CLEARED TITLE :";
		std::cout << s->title_cleared() << endl;
		std::cout << "VIDEO URL :";
		std::cout << s->video_url_raw << endl;
		std::cout << "IMAGE URL :";
		std::cout << s->image_url_raw << endl;
		std::cout << "DESCRIPTION :";
		std::cout << s->description_raw << endl;
		std::cout << "CLEARED DESCRIPTION :";
		std::cout << s->description_cleared() << endl;

	}
}

int main()
{
	test_simple();
	test();
	test_video();

    return 0;
}

