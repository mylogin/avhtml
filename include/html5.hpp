
#pragma once

#include <memory>
#include <functional>

#include <string>
#include <vector>

#include <boost/coroutine/asymmetric_coroutine.hpp>

namespace html{

	class dom;
	typedef std::shared_ptr<dom> dom_ptr;
	typedef std::weak_ptr<dom> dom_weak_ptr;

	class selector
	{
	public:
		selector(const std::string&);
		selector(std::string&&);

		selector(const char* s)
			: selector(std::string(s))
		{}

		template<int N>
		selector(const char s[N])
			: selector(std::string(s))
		{};

		friend class dom;

	protected:

		struct selector_matcher{
			bool operator()(const dom&) const;

		private:
			std::string matching_tag_name;
			std::string matching_id;
			std::string matching_class;
			std::string matching_name;
			std::string matching_index;
		};

		std::vector<selector_matcher>::const_iterator begin() const {
			return m_matchers.begin();
		}

		std::vector<selector_matcher>::const_iterator end() const {
			return m_matchers.end();
		}

	private:
		void build_matchers();

		std::vector<selector_matcher> m_matchers;

		std::string m_select_string;
	};

	class dom
	{

	public:

		// 默认构造.
		dom(dom* parent = nullptr) noexcept;

		// 从html构造 DOM.
		explicit dom(const std::string& html_page, dom* parent = nullptr);

	public:
		// 喂入一html片段.
		bool append_partial_html(const std::string &);

	public:
		dom operator[](const selector&);

		std::string to_html();

		std::string to_plain_text();

	private:

		void html_parser(boost::coroutines::asymmetric_coroutine<char>::pull_type & html_page_source);
		boost::coroutines::asymmetric_coroutine<char>::push_type html_parser_feeder;

	protected:
		std::map<std::string, std::string> attributes;
		std::string tag_name;

		std::vector<std::string> contents;

		std::vector<dom_ptr> children;
		dom* m_parent;

		template<class T>
		static void dom_walk(html::dom_ptr d, T handler);

		friend class selector;
	};
};
