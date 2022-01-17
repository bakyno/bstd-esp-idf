#pragma once

#include <cJSON.h>


namespace bstd {


class cJSONDocument
{
	public:

		class Item
		{
			public:
				Item( cJSON *item ) { m_item = item; }

				explicit operator bool() const { return m_item; }

				bool is_null() const { return (m_item && cJSON_IsNull( m_item )); }

				bool is_bool() const { return (m_item && cJSON_IsBool( m_item )); }
				bool get( bool def ) const { return is_bool() ? m_item->valueint : def; }

				bool is_integer() const { return (m_item && cJSON_IsNumber( m_item )); }
				int get( int def ) const { return is_integer() ? m_item->valueint : def; }

				bool is_real() const { return (m_item && cJSON_IsNumber( m_item )); }
				double get( double def ) const { return is_real() ? m_item->valuedouble : def; }

				bool is_string() const { return (m_item && cJSON_IsString( m_item )); }
				const char * get( const char *def ) const { return is_string() ? m_item->valuestring : def; }

				bool is_array() const { return (m_item && cJSON_IsArray( m_item )); }
				size_t size() const { return is_array() ? cJSON_GetArraySize( m_item ) : 0; }
				Item operator[] ( size_t index ) { return is_array() ? cJSON_GetArrayItem( m_item, index ) : nullptr; }
				const Item operator[] ( size_t index ) const { return is_array() ? cJSON_GetArrayItem( m_item, index ) : nullptr; }

				bool is_object() const { return (m_item && cJSON_IsObject( m_item )); }
				Item operator[] ( const char *name ) { return m_item ? cJSON_GetObjectItemCaseSensitive( m_item, name ) : nullptr; }
				const Item operator[] ( const char *name ) const { return m_item ? cJSON_GetObjectItemCaseSensitive( m_item, name ) : nullptr; }

			private:
				cJSON *m_item = nullptr;
		};

	public:

		cJSONDocument() {};
		cJSONDocument( const char *data ) { parse( data ); }
		~cJSONDocument() { close(); }

		bool parse( const char *data )
		{
			close();
			m_doc = cJSON_Parse( data );
			return m_doc;
		}

		void close()
		{
			if ( m_doc )
			{
				cJSON_Delete( m_doc );
				m_doc = nullptr;
			}
		}

		const char * error_ptr() const { return cJSON_GetErrorPtr(); }

		explicit operator bool() const { return m_doc; }

		Item operator[] (  const char *name ) { return m_doc ? cJSON_GetObjectItemCaseSensitive( m_doc, name ) : nullptr; }
		const Item operator[] (  const char *name ) const { return m_doc ? cJSON_GetObjectItemCaseSensitive( m_doc, name ) : nullptr; }

	private:
		cJSON *m_doc = nullptr;
};


}; // namespace bstd
