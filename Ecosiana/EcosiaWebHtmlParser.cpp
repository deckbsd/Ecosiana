#include "EcosiaWebHtmlParser.h"

void EcosiaWebHtmlParser::parse(char* sz_buffer, list<EcosiaWebResult> &ls)
{
	GumboOutput* output;

	output = EcosiaHtmlParser::parse(sz_buffer);
	parse_web_results(output->root,ls);
	gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void WINAPI EcosiaWebHtmlParser::parse_web_results(GumboNode* html, list<EcosiaWebResult> &ls)
{
	if (html->type != GUMBO_NODE_ELEMENT)
	{
		return;
	}

	if (html->v.element.tag == GUMBO_TAG_DIV)
	{
		if (gumbo_get_attribute(&html->v.element.attributes, "class") != nullptr)
		{
			if (strcmp(gumbo_get_attribute(&html->v.element.attributes, "class")->value, "result js-result card-mobile") == 0)
			{
				EcosiaWebResult result;

				GumboVector* children = &html->v.element.children;
				for (unsigned int i = 0; i < children->length; ++i) {
					GumboNode* bloc_node = static_cast<GumboNode*>(children->data[i]);

					//title
					if (bloc_node->v.element.tag == GUMBO_TAG_A && strcmp(gumbo_get_attribute(&bloc_node->v.element.attributes, "class")->value, "result-title js-result-title") == 0)
					{

						for (unsigned int i = 0; i < bloc_node->v.element.children.length; i++)
						{
							GumboNode* title_text = static_cast<GumboNode*>(bloc_node->v.element.children.data[i]);

							if (title_text->v.element.tag == GUMBO_TAG_B)
							{
								GumboNode* b_tag = static_cast<GumboNode*>(title_text->v.element.children.data[0]);

								result.title_raw += b_tag->v.text.text;
								
							}

							if (title_text->type == GUMBO_NODE_TEXT)
							{
								result.title_raw += title_text->v.text.text;
							}
						}
					}

					//description
					if (bloc_node->v.element.tag == GUMBO_TAG_P && strcmp(gumbo_get_attribute(&bloc_node->v.element.attributes, "class")->value, "result-snippet") == 0)
					{

						for (unsigned int i = 0; i < bloc_node->v.element.children.length; i++)
						{
							GumboNode* desc_text = static_cast<GumboNode*>(bloc_node->v.element.children.data[i]);

							if (desc_text->v.element.tag == GUMBO_TAG_B)
							{
								GumboNode* b_tag = static_cast<GumboNode*>(desc_text->v.element.children.data[0]);

								result.description_raw += b_tag->v.text.text;
							}

							if (desc_text->type == GUMBO_NODE_TEXT)
							{
								result.description_raw += desc_text->v.text.text;
							}

						}


					}

					// URL
					if (bloc_node->v.element.tag == GUMBO_TAG_A && strcmp(gumbo_get_attribute(&bloc_node->v.element.attributes, "class")->value, "result-url js-result-url") == 0)
					{
						result.url_raw = gumbo_get_attribute(&bloc_node->v.element.attributes, "href")->value;
					}
				}

				ls.push_back(result);
			}
		}

	}

	GumboVector* children = &html->v.element.children;
	for (unsigned int i = 0; i < children->length; ++i) {
		parse_web_results(static_cast<GumboNode*>(children->data[i]), ls);
	}
}

EcosiaWebHtmlParser::EcosiaWebHtmlParser()
{
}


EcosiaWebHtmlParser::~EcosiaWebHtmlParser()
{
}
