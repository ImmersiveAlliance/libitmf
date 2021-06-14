#include <itmfunits.h>

namespace itmflib {
	ITMF_HEADER ITMF_HEADER::CreateITMFHeader(int32_t flags)
	{
		return ITMF_HEADER(BMLstring(1, "OX"), BMLint(2, 1), BMLint(3, flags));
	}

	ITMF_HEADER ITMF_HEADER::ReadITMFHeader(std::ifstream& infile) {
		// Confirm OX
		BMLstring ox;
		if (ParseElement(infile, static_cast<int>(ITMF_HEADER_IDS::OX), ox)) {
			if (ox.getValue() != "OX") {
				// TODO: Error: header string was not "OX"
			}
		} else {
			// TODO: Error: Expected header string not found
		}

		// Confirm Version
		BMLint version;
		if (ParseElement(infile, static_cast<int>(ITMF_HEADER_IDS::VERSION), version)) {
			if (version.getValue() > ITMF_CONTAINER_VERSION) {
				// TODO: Error: ITMF file version not supported
			}
		}
		else {
			// TODO: Error: ITMF version number not found
		}

		// Read flags
		BMLint flags;
		if (ParseElement(infile, static_cast<int>(ITMF_HEADER_IDS::FLAGS), flags)) {
			// Successfully parsed flags
		}
		else {
			// TODO: Error: ITMF version number not found
		}

		// TODO: Read optional data

		return ITMF_HEADER(ox, version, flags);
	}

	bool ITMF_HEADER::hasFlag(ITMF_HEADER_FLAGS flag)
	{
		return (flags.getValue() & static_cast<int32_t>(flag)) != 0;
	}

	size_t ITMF_HEADER::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;
		bytes_written += ox.save(outfile);
		bytes_written += version.save(outfile);
		bytes_written += flags.save(outfile);

		if (CHECK_BOOST_OPTIONAL(keygen_method))
			boost::apply_visitor(save_visitor(outfile, bytes_written), keygen_method.get());
		if (CHECK_BOOST_OPTIONAL(nrounds))
			bytes_written += nrounds.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(salt))
			bytes_written += salt.get().save(outfile);
	
		return bytes_written;
	}

	void PROPERTIES::parseProperties(std::ifstream& infile) {
		// Parse key-value pairs until we hit a close tag, then break the loop
		// TODO: Bound check this loop
		int current_id, current_type;
		peekTag(infile, current_id, current_type);
		while (current_type != static_cast<int>(BML_TYPES::CLOSE)) {
			std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> pair;

			BMLstring key;
			if (ParseElement(infile, static_cast<int>(PROPERTIES_IDS::KEY), key)) {
				pair.first = key;
			}
			else {
				// TODO: Error: Badly formed key element
			}

			BMLstring value_as_string;
			BMLlong value_as_long;
			int value_id = static_cast<int>(PROPERTIES_IDS::VALUE);
			if (ParseElement(infile, value_id, value_as_string))
				pair.second = value_as_string;
			else if (ParseElement(infile, value_id, value_as_long))
				pair.second = value_as_long;
			else {
				// TODO: Error: badly formed value element
			}

			properties.push_back(pair);

			peekTag(infile, current_id, current_type);
		}

		// Move past close tag
		infile.get();

		if (current_id != static_cast<int>(LOGICAL_UNIT_IDS::PROPERTIES)) {
			// TODO: Warning: Wrong ID on Properties close tag
		}

	}

	/*size_t ITMF_HEADER::writeToBuffer(std::vector<char>* buffer)
	{
		size_t bytes_written = 0;
		bytes_written += ox.writeToBuffer(buffer);
		bytes_written += version.writeToBuffer(buffer);
		bytes_written += flags.writeToBuffer(buffer);

		if (CHECK_BOOST_OPTIONAL(keygen_method))
			boost::apply_visitor(buffer_save_visitor(buffer, bytes_written), keygen_method.get());
		if (CHECK_BOOST_OPTIONAL(nrounds))
			bytes_written += nrounds.get().writeToBuffer(buffer);
		if (CHECK_BOOST_OPTIONAL(salt))
			bytes_written += salt.get().writeToBuffer(buffer);

		return bytes_written;
	}*/

	size_t PROPERTIES::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;
		bytes_written += writeOpenTag(outfile);

		for (std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> &prop : properties) {
			bytes_written += prop.first.save(outfile);
			boost::apply_visitor(save_visitor(outfile, bytes_written), prop.second);
		}

		bytes_written += writeCloseTag(outfile);

		return bytes_written;
	}

	STREAMHEADERS STREAM_HEADER::ReadStreamHeaders(std::ifstream& infile)
	{
		STREAMHEADERS streamheaders;

		int current_id, current_type, peeked_id, peeked_type;
		do {
			decodeTag(infile, current_id, current_type);
			if (current_id == static_cast<int>(LOGICAL_UNIT_IDS::STREAM_HEADERS) && current_type == static_cast<int>(BML_TYPES::OBJECT)) {

				STREAM_HEADER header;

				// Parse each element in the StreamHeader logical unit
				
				// type
				BMLint type_as_int;
				BMLstring type_as_string;
				int type_id = static_cast<int>(STREAM_HEADER_IDS::TYPE);
				if (ParseElement(infile, type_id, type_as_int)) 
					header.type = type_as_int;
				else if (ParseElement(infile, type_id, type_as_string)) 
					header.type = type_as_string;
				else {
					// TODO: Error: Invalid type element
				}

				// flags
				BMLint flags;
				if (ParseElement(infile, static_cast<int>(STREAM_HEADER_IDS::FLAGS), flags)) 
					header.flags = flags;
				
				// codec
				BMLint codec_as_int;
				BMLstring codec_as_string;
				int codec_id = static_cast<int>(STREAM_HEADER_IDS::CODEC);
				if (ParseElement(infile, codec_id, codec_as_int)) 
					// '=' operator is ambiguous since this is an optional containing a variant, so we use '*' instead
					*(header.codec) = codec_as_int;
				else if (ParseElement(infile, codec_id, codec_as_string)) 
					// '=' operator is ambiguous since this is an optional containing a variant, so we use '*' instead
					*(header.codec) = codec_as_string;

				// format
				BMLblob format;
				if (ParseElement(infile, static_cast<int>(STREAM_HEADER_IDS::FORMAT), format)) 
					header.format = format;

				// nchunks
				BMLlong nchunks;
				if (ParseElement(infile, static_cast<int>(STREAM_HEADER_IDS::NCHUNKS), nchunks)) 
					header.nchunks = nchunks;

				// nbytes
				BMLlong nbytes;
				if (ParseElement(infile, static_cast<int>(STREAM_HEADER_IDS::NBYTES), nbytes)) 
					header.nbytes = nbytes;

				// key-value pairs
				int current_id, current_type;
				peekTag(infile, current_id, current_type);
				int key_id = static_cast<int>(STREAM_HEADER_IDS::KEY);
				int value_id = static_cast<int>(STREAM_HEADER_IDS::VALUE);
				while (current_id == key_id) {
					std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> pair;

					BMLstring key;
					if (ParseElement(infile, key_id, key))
						pair.first = key;
					else {
						// TODO: Error: badly formed key element
					}

					BMLstring value_as_string;
					BMLlong value_as_long;
					if (ParseElement(infile, value_id, value_as_string))
						pair.second = value_as_string;
					else if (ParseElement(infile, value_id, value_as_long))
						pair.second = value_as_long;
					else {
						// TODO: Error: badly formed value element
					}

					header.properties.push_back(pair);

					peekTag(infile, current_id, current_type);
				}

				// cipher
				BMLint cipher_as_int;
				BMLstring cipher_as_string;
				int cipher_id = static_cast<int>(STREAM_HEADER_IDS::CIPHER);
				if (ParseElement(infile, cipher_id, cipher_as_int))
					// '=' operator is ambiguous since this is an optional containing a variant, so we use '*' instead
					*(header.cipher) = cipher_as_int;
				else if (ParseElement(infile, cipher_id, cipher_as_string)) 
					// '=' operator is ambiguous since this is an optional containing a variant, so we use '*' instead
					*(header.cipher) = cipher_as_string;

				// salt
				BMLblob salt;
				if (ParseElement(infile, static_cast<int>(STREAM_HEADER_IDS::SALT), salt))
					header.salt = salt;

				// signature
				BMLblob signature;
				if (ParseElement(infile, static_cast<int>(STREAM_HEADER_IDS::SIGNATURE), signature))
					header.signature = signature;

				// Close tag
				decodeTag(infile, current_id, current_type);
				if (current_type != static_cast<int>(BML_TYPES::CLOSE)) {
					// TODO: Error: Missing close tag
				}
				if (current_id != static_cast<int>(LOGICAL_UNIT_IDS::STREAM_HEADERS)) {
					// TODO: Warning: Close tag had wrong ID
				}

				streamheaders.push_back(header);
			}
			else {
				// TODO: Error: Expected stream header, got something else
			}

			peekTag(infile, peeked_id, peeked_type);
		} while (peeked_type != static_cast<int>(BML_TYPES::CLOSE)); // TODO: Handle EOF

		// Move past close tag
		infile.get();

		return streamheaders;
	}

	
	/*size_t PROPERTIES::writeToBuffer(std::vector<char>* buffer) {
		size_t bytes_written = 0;
		bytes_written += writeOpenTagToBuffer(buffer);

		for (std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>& prop : properties) {
			bytes_written += prop.first.writeToBuffer(buffer);
			boost::apply_visitor(buffer_save_visitor(buffer, bytes_written), prop.second);
		}

		bytes_written += writeCloseTagToBuffer(buffer);

		return bytes_written;
	}*/

	size_t STREAM_HEADER::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;
		bytes_written += writeOpenTag(outfile);

		boost::apply_visitor(save_visitor(outfile, bytes_written), type);

		if (CHECK_BOOST_OPTIONAL(flags))
			bytes_written += flags.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(codec))
			boost::apply_visitor(save_visitor(outfile, bytes_written), codec.get());
		if (CHECK_BOOST_OPTIONAL(format))
			bytes_written += format.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(nchunks))
			bytes_written += nchunks.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(nbytes))
			bytes_written += nbytes.get().save(outfile);
		for (std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>& prop : properties) {
			bytes_written += prop.first.save(outfile);
			boost::apply_visitor(save_visitor(outfile, bytes_written), prop.second);
		}
		if (CHECK_BOOST_OPTIONAL(cipher))
			boost::apply_visitor(save_visitor(outfile, bytes_written), cipher.get());
		if (CHECK_BOOST_OPTIONAL(salt))
			bytes_written += salt.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(signature))
			bytes_written += signature.get().save(outfile);
		
		bytes_written += writeCloseTag(outfile);

		return bytes_written;
	}

	INDEXES INDEX::ReadIndexes(std::ifstream& infile)
	{
		INDEXES indexes;

		int current_id, current_type, peeked_id, peeked_type;

		peekTag(infile, peeked_id, peeked_type);
		while (peeked_type != static_cast<int>(BML_TYPES::CLOSE)) {
			decodeTag(infile, current_id, current_type);
			if (current_id == static_cast<int>(LOGICAL_UNIT_IDS::INDEX) && current_type == static_cast<int>(BML_TYPES::OBJECT)) {

				INDEX index;

				// Parse each element in the Index object

				// stream index - int 
				BMLint stream_index;
				if (ParseElement(infile, static_cast<int>(INDEX_IDS::STREAM_INDEX), stream_index)) {
					index.stream_index = stream_index;
				}
				
				while (true) {
					std::pair<BMLlong, boost::optional<BMLlong>> pair;
					if (ParseElement(infile, static_cast<int>(INDEX_IDS::POS_DELTA), pair.first)) {
						// Successful
					}
					else {
						// Encountered end of repeated section
						break;
					}

					BMLlong nbytes;
					if (ParseElement(infile, static_cast<int>(INDEX_IDS::NBYTES), nbytes)) {
						// Successful
						pair.second = nbytes;
					}
					else {
						pair.second = boost::none;
					}

					index.nbytes.push_back(pair);
				}
				
				// Close tag
				decodeTag(infile, current_id, current_type);
				if (current_type != static_cast<int>(BML_TYPES::CLOSE)) {
					// TODO: Error: Missing close tag
				}
				if (current_id != static_cast<int>(LOGICAL_UNIT_IDS::INDEX)) {
					// TODO: Warning: Close tag had wrong ID
				}

				indexes.push_back(index);
			}
			else {
				// TODO: Error: Expected index, got something else
			}

			peekTag(infile, peeked_id, peeked_type);
		}

		// Move past close tag
		infile.get();

		if (peeked_id != static_cast<int>(LOGICAL_UNIT_IDS::INDEX)) {
			// TODO: Warning: Close tag had the wrong ID
		}

		return indexes;
	}

	size_t INDEX::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;
		bytes_written += writeOpenTag(outfile);

		if (CHECK_BOOST_OPTIONAL(stream_index))
			bytes_written += stream_index.get().save(outfile);

		for (std::pair<BMLlong, boost::optional<BMLlong>>& rep : nbytes) {
			bytes_written += rep.first.save(outfile);
			if (CHECK_BOOST_OPTIONAL(rep.second)) {
				bytes_written += rep.second.get().save(outfile);
			}
		}

		bytes_written += writeCloseTag(outfile);

		return bytes_written;
	}

	size_t FILE_PROPERTIES::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;

		if (CHECK_BOOST_OPTIONAL(chunk_index))
			bytes_written += chunk_index.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(offset))
			bytes_written += offset.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(nbytes))
			bytes_written += nbytes.get().save(outfile);
		bytes_written += name.save(outfile);
		if (CHECK_BOOST_OPTIONAL(sha256))
			bytes_written += sha256.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(flags))
			bytes_written += flags.get().save(outfile);
		for (std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>& prop : properties) {
			bytes_written += prop.first.save(outfile);
			boost::apply_visitor(save_visitor(outfile, bytes_written), prop.second);
		}

		return bytes_written;
	}

	DIRECTORIES DIRECTORY::ReadDirectories(std::ifstream& infile)
	{
		DIRECTORIES directories;

		int current_id, current_type, peeked_id, peeked_type;

		peekTag(infile, peeked_id, peeked_type);
		while (peeked_type != static_cast<int>(BML_TYPES::CLOSE)) {
			decodeTag(infile, current_id, current_type);
			if (current_id == static_cast<int>(LOGICAL_UNIT_IDS::DIRECTORY) && current_type == static_cast<int>(BML_TYPES::OBJECT)) {

				DIRECTORY directory;

				// Parse each element in the Index object

				// stream index - int 
				BMLint stream_index;
				if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::STREAM_INDEX), stream_index)) {
					directory.stream_index = stream_index;
				}

				
				while (true) {
					FILE_PROPERTIES file_properties;
					BMLlong chunk_index;
					if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::CHUNK_INDEX), chunk_index))
						file_properties.setChunkIndex(chunk_index);

					BMLlong offset;
					if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::OFFSET), offset))
						file_properties.setOffset(offset);

					BMLlong nbytes;
					if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::NBYTES), nbytes))
						file_properties.setNumBytes(nbytes);

					BMLstring name;
					if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::NAME), name))
						file_properties.setName(name);
					else
						// Encountered end of repeated section
						break;

					BMLblob sha256;
					if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::SHA256), sha256))
						file_properties.setSha256(sha256);

					BMLint flags;
					if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::FLAGS), flags))
						file_properties.setFlags(flags);

					while (true) {
						std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> pair;
						if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::KEY), pair.first)) {
							// Successful
						}
						else {
							break;
						}

						BMLstring value_as_string;
						BMLlong value_as_long;
						if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::VALUE), value_as_string)) {
							pair.second = value_as_string;
						}
						else if (ParseElement(infile, static_cast<int>(DIRECTORY_IDS::VALUE), value_as_long)) {
							pair.second = value_as_long;
						}
						else {
							// TODO: Error: a key was read without a corresponding value 
						}

						file_properties.addProperty(pair);
					}


					directory.file_properties.push_back(file_properties);
				}
				
				// Close tag
				decodeTag(infile, current_id, current_type);
				if (current_type != static_cast<int>(BML_TYPES::CLOSE)) {
					// TODO: Error: Missing close tag
				}
				if (current_id != static_cast<int>(LOGICAL_UNIT_IDS::DIRECTORY)) {
					// TODO: Warning: Close tag had wrong ID
				}

				directories.push_back(directory);
			}
			else {
				// TODO: Error: Expected index, got something else
			}

			peekTag(infile, peeked_id, peeked_type);
		}

		// Move past close tag
		infile.get();

		if (peeked_id != static_cast<int>(LOGICAL_UNIT_IDS::DIRECTORY)) {
			// TODO: Warning: Close tag had the wrong ID
		}

		return directories;
	}

	size_t DIRECTORY::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;

		bytes_written += writeOpenTag(outfile);

		if (CHECK_BOOST_OPTIONAL(stream_index))
			bytes_written += stream_index.get().save(outfile);

		for (FILE_PROPERTIES& prop : file_properties) {
			bytes_written += prop.write(outfile);
		}

		bytes_written += writeCloseTag(outfile);

		return bytes_written;
	}

	void SIGNATURE::parseSignature(std::ifstream& infile)
	{
		BMLint alg_as_int;
		BMLstring alg_as_string;
		if (ParseElement(infile, static_cast<int>(SIGNATURE_IDS::ALGORITHM), alg_as_int))
			this->algorithm = alg_as_int;
		else if (ParseElement(infile, static_cast<int>(SIGNATURE_IDS::ALGORITHM), alg_as_string))
			this->algorithm = alg_as_string;
		else {
			// TODO: Error: Missing algorithm
		}

		BMLblob cert;
		if (ParseElement(infile, static_cast<int>(SIGNATURE_IDS::CERTIFICATE), cert))
			this->certificate = cert;

		BMLblob sig;
		if (ParseElement(infile, static_cast<int>(SIGNATURE_IDS::SIGNATURE), sig))
			this->signature = sig;
		else {
			// TODO: Error: Missing signature
		}
	}

	size_t SIGNATURE::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;

		bytes_written += writeOpenTag(outfile);

		boost::apply_visitor(save_visitor(outfile, bytes_written), algorithm);
		if (CHECK_BOOST_OPTIONAL(certificate))
			bytes_written += certificate.get().save(outfile);
		bytes_written += signature.save(outfile);

		bytes_written += writeCloseTag(outfile);

		return bytes_written;
	}

	CHUNKS CHUNK::ReadChunks(std::ifstream& infile)
	{
		CHUNKS stream;
		int peeked_id, peeked_type;
		// Note that we use a do-while loop because the stream must have at least one chunk, which may be empty
		do {
			boost::optional<BMLint> maybe_stream_index;
			boost::optional<BMLint> maybe_flags;
			boost::optional<BMLlong> maybe_uncompressed_nbytes;
			int current_id = 0, current_type = 0;
			BMLblob data;

			BMLint stream_index; 
			if (ParseElement(infile, static_cast<int>(CHUNK_IDS::STREAM_INDEX), stream_index)) {
				maybe_stream_index = stream_index;
			}
			else {
				maybe_stream_index = boost::none;
			}

			BMLint flags; 
			if (ParseElement(infile, static_cast<int>(CHUNK_IDS::FLAGS), flags)) {
				maybe_flags = flags;
			}
			else {
				maybe_flags = boost::none;
			}

			BMLlong uncompressed_nbytes; 
			if (ParseElement(infile, static_cast<int>(CHUNK_IDS::UNCOMPRESSED_NBYTES), uncompressed_nbytes)) {
				maybe_uncompressed_nbytes = uncompressed_nbytes;
			}
			else {
				maybe_uncompressed_nbytes = boost::none;
			}

			if (ParseElement(infile, static_cast<int>(CHUNK_IDS::DATA), data)) {
				// Successful
			}
			else {
				// TODO: Error: Chunk missing data 
			}

			CHUNK chunk(data, maybe_stream_index, maybe_flags, maybe_uncompressed_nbytes);

			stream.push_back(chunk);

			// If the next tag is not from a chunk or we've hit the end of the file, the streams are finished
			peekTag(infile, peeked_id, peeked_type); 
		} while (peeked_type != static_cast<int>(BML_TYPES::OBJECT)); // TODO: handle EOF, probably with std::error_code

		return stream;
	}

	size_t CHUNK::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;

		if (CHECK_BOOST_OPTIONAL(stream_index))
			bytes_written += stream_index.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(flags))
			bytes_written += flags.get().save(outfile);
		if (CHECK_BOOST_OPTIONAL(uncompressed_bytes))
			bytes_written += uncompressed_bytes.get().save(outfile);
		bytes_written += data.save(outfile);

		return bytes_written;
	}

	ITMF_FOOTER ITMF_FOOTER::CreateFooter(uint32_t offset)
	{
		ITMF_FOOTER footer;
		footer.offset_to_stream_end = offset;

		return footer;
	}

	void ITMF_FOOTER::parseFooter(std::ifstream& infile)
	{
		char bytes[4];
		unsigned char* ubytes = reinterpret_cast<unsigned char*>(bytes);
		infile.read(bytes, 4);
		this->offset_to_stream_end = ubytes[0] | ubytes[1] << 8 | ubytes[2] << 16 | ubytes[3] << 24;
		infile.read(bytes, 4);
		this->magic = ubytes[0] | ubytes[1] << 8 | ubytes[2] << 16 | ubytes[3] << 24;
		if (ITMF_FOOTER::EXPECTED_MAGIC != this->magic) {
			// TODO: Magic value in footer not as expected
		}
	}

	void ITMF_FOOTER::write(std::ofstream& outfile)
	{
		outfile.write((char*)&offset_to_stream_end, sizeof(offset_to_stream_end));
		outfile.write((char*)&magic, sizeof(magic));
	}
}