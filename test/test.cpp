
#include <html5.hpp>
#include <fstream>
#include <iostream>


const char msg_usage[] = "\nusage : %s <html file name> <selector>\n\n";

void test();


void callback(std::shared_ptr<html::dom>)
{
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		if (argc > 0)
			printf(msg_usage, argv[0]);
		else
			printf(msg_usage, "html5test");
	}
	else {
		html::dom cu_page;
		std::ifstream ifs;

		std::istream * instream;

		std::string infile = argv[1];

		if (infile == "-")
		{
			instream = &std::cin;
		}
		else
		{
			ifs.open(infile.c_str());
			instream = & ifs;
		}

		(*instream) >> std::noskipws;

		std::string test_page((std::istreambuf_iterator<char>(* instream)), std::istreambuf_iterator<char>());

		std::cout << "callback usage: " << std::endl;

		cu_page.append_partial_html(test_page) | argv[2] | [](html::tag_stage s, std::shared_ptr<html::dom> d) {
			if(s == html::tag_open) {
				std::cout << d->to_html() << std::endl;	
			}
		};

		std::cout << std::endl << "basic usage: " << std::endl;
	
		std::cout << cu_page[argv[2]].to_html() << std::endl;
	}
}

void test()
{
	html::dom page;
	html::dom page_href_http_node;

	page.append_partial_html("<html><head>");
	page.append_partial_html("<title id=\"id_test\" href=\"http://www.baidu.com\" bkcolor=\"ff000000\" textcolor=\"ffffffff\">hello world</title");
	page.append_partial_html("></head></html>");

	page = page["title:first"];
	printf("value : %s \n", page.to_plain_text().c_str());
	page = page["title:eq(1)"];
	printf("value : %s \n", page.to_plain_text().c_str());

	page = page["#id_test"];
	printf("value : %s \n", page.to_plain_text().c_str());

	page["[href]"];
	printf("value : %s \n", page.to_plain_text().c_str());

	page = page["[href$='http']"];
	printf("value : %s \n", page.to_plain_text().c_str());

	page = page["[bkcolor='ff000000']"];
	printf("value : %s \n", page.to_plain_text().c_str());

	page = page["[textcolor!='ff000000']"];
	printf("value : %s \n", page.to_plain_text().c_str());

}
