#include "EcosiaVideoHtmlParser.h"

void EcosiaVideoHtmlParser::parse(char* sz_buffer, list<EcosiaVideoResult> &ls)
{
	GumboOutput* output;

	output = EcosiaHtmlParser::parse(sz_buffer);
	parse_video_results(output->root, ls);
	gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void WINAPI EcosiaVideoHtmlParser::parse_video_results(GumboNode* html, list<EcosiaVideoResult> &ls)
{
	if (html->type != GUMBO_NODE_ELEMENT)
	{
		return;
	}

	if (html->v.element.tag == GUMBO_TAG_DIV)
	{
		if (gumbo_get_attribute(&html->v.element.attributes, "class") != nullptr)
		{
			if (strcmp(gumbo_get_attribute(&html->v.element.attributes, "class")->value, "result result-media card-mobile") == 0)
			{
				EcosiaVideoResult result;

				GumboVector* children = &html->v.element.children;
				for (unsigned int i = 0; i < children->length; ++i) {
					GumboNode* bloc_node = static_cast<GumboNode*>(children->data[i]);

					//title
					if (bloc_node->v.element.tag == GUMBO_TAG_A && strcmp(gumbo_get_attribute(&bloc_node->v.element.attributes, "class")->value, "result-title") == 0)
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
					if (bloc_node->v.element.tag == GUMBO_TAG_P && strcmp(gumbo_get_attribute(&bloc_node->v.element.attributes, "class")->value, "result-metadata") == 0)
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

					// URL VIDEO
					if (bloc_node->v.element.tag == GUMBO_TAG_P && strcmp(gumbo_get_attribute(&bloc_node->v.element.attributes, "class")->value, "result-snippet") == 0)
					{
						for (unsigned int i = 0; i < bloc_node->v.element.children.length; i++)
						{
							GumboNode* url_video = static_cast<GumboNode*>(bloc_node->v.element.children.data[i]);

							if (url_video->v.element.tag == GUMBO_TAG_A && strcmp(gumbo_get_attribute(&url_video->v.element.attributes, "class")->value, "result-url result-url-video") == 0)
							{
								result.video_url_raw = gumbo_get_attribute(&url_video->v.element.attributes, "href")->value;
							}
						}
					}

					// URL IMAGE
					if (bloc_node->v.element.tag == GUMBO_TAG_DIV && strcmp(gumbo_get_attribute(&bloc_node->v.element.attributes, "class")->value, "video-result left") == 0)
					{
						for (unsigned int i = 0; i < bloc_node->v.element.children.length; i++)
						{
							GumboNode* url_image = static_cast<GumboNode*>(bloc_node->v.element.children.data[i]);

							if (url_image->v.element.tag == GUMBO_TAG_IMG && strcmp(gumbo_get_attribute(&url_image->v.element.attributes, "class")->value, "thumbnail-image js-image") == 0)
							{
								result.image_url_raw = gumbo_get_attribute(&url_image->v.element.attributes, "data-src")->value;
							}
						}
					}
				}

				ls.push_back(result);
			}
		}

	}

	GumboVector* children = &html->v.element.children;
	for (unsigned int i = 0; i < children->length; ++i) {
		parse_video_results(static_cast<GumboNode*>(children->data[i]), ls);
	}
}


EcosiaVideoHtmlParser::EcosiaVideoHtmlParser()
{
}


EcosiaVideoHtmlParser::~EcosiaVideoHtmlParser()
{
}
