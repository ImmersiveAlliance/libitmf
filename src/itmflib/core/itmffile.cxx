#include <itmffile.h>

namespace itmflib {
    /**
    Creates a standard ITMF file with encoding order StreamsAtStart. Will include
    logical units that are non-optional: ITMF Header, Stream, StreamHeader, Chunk,
    Directory, and Footer.
    */
    ITMFFILE ITMFFILE::CreateStreamsAtStartFile() {
        ITMFCONFIGURATION config(ITMF_ENCODING_ORDER::STREAMS_AT_START, false, false,
            ITMF_SIGNATURE::NONE, ITMF_COMPRESSION::NONE);

        int32_t flags = static_cast<int32_t>(config.getEncodingOrder());
        // Directory is included so add flag
        flags += static_cast<int32_t>(ITMF_HEADER_FLAGS::DIRECTORY);

        ITMF_HEADER header = ITMF_HEADER::CreateITMFHeader(flags);

        ITMF_FOOTER footer = ITMF_FOOTER::CreateFooter(0); // offset will need to be updated

        return ITMFFILE(header, footer, config);
    }

    ITMFFILE ITMFFILE::CreateStreamsAtEndFile() {
        ITMFCONFIGURATION config(ITMF_ENCODING_ORDER::STREAMS_AT_END, false, false,
            ITMF_SIGNATURE::NONE, ITMF_COMPRESSION::NONE);

        int32_t flags = static_cast<int32_t>(config.getEncodingOrder());
        // Directory is included so add flag
        flags += static_cast<int32_t>(ITMF_HEADER_FLAGS::DIRECTORY);

        ITMF_HEADER header = ITMF_HEADER::CreateITMFHeader(flags);

        ITMF_FOOTER footer = ITMF_FOOTER::CreateFooter(0); // offset will need to be updated

        return ITMFFILE(header, footer, config);
    }

    ITMFFILE ITMFFILE::CreateFileFromConfig(ITMFCONFIGURATION configuration) {
        int32_t flags = static_cast<int32_t>(configuration.getEncodingOrder());
        // Directory is included so add flag
        flags += static_cast<int32_t>(ITMF_HEADER_FLAGS::DIRECTORY);

        ITMF_HEADER header = ITMF_HEADER::CreateITMFHeader(flags);

        ITMF_FOOTER footer = ITMF_FOOTER::CreateFooter(0); // offset will need to be updated
        ITMFFILE file = ITMFFILE(header, footer, configuration);
        if (configuration.isPropertiesIncluded()) {
            file.header.addFlag(ITMF_HEADER_FLAGS::PROPERTIES);
            file.properties = PROPERTIES();
        }
        if (configuration.isIndexIncluded()) {
            file.header.addFlag(ITMF_HEADER_FLAGS::INDEX);
            file.index = INDEXES({});
        }

        return file;
    }

    ITMFFILE ITMFFILE::ReadFile(std::string filepath) {
        std::ifstream infile;
        infile.open(filepath, std::ios::in | std::ios::binary);
        
        ITMFFILE itmffile;
        if (infile.is_open()) {
            int current_id = 0;
            int current_type = 0;

            itmffile.header = ITMF_HEADER::ReadITMFHeader(infile);

            // Set file config according to header flags
			ITMF_ENCODING_ORDER eo = itmffile.header.hasFlag(ITMF_HEADER_FLAGS::STREAMS_AT_START) ? ITMF_ENCODING_ORDER::STREAMS_AT_START : ITMF_ENCODING_ORDER::STREAMS_AT_END;
			bool has_properties = itmffile.header.hasFlag(ITMF_HEADER_FLAGS::PROPERTIES);
			bool has_index = itmffile.header.hasFlag(ITMF_HEADER_FLAGS::INDEX);
			// TODO: This must be updated with the correct logic once encryption and compression are implemented in itmflib.
			ITMF_SIGNATURE signature = ITMF_SIGNATURE::NONE;
			ITMF_COMPRESSION com = ITMF_COMPRESSION::NONE;
			ITMFCONFIGURATION c(eo, has_properties, has_index, signature, com);
			itmffile.config = c;

            // Check for properties present before streams, regardless of StreamsAtEnd or StreamsAtStart
            // For compatibility with earlier versions of OTOY's ORBX container, we
            // check for the Properties unit encoded at this point in all cases. In
            // If properties are present, read properties
            peekTag(infile, current_id, current_type);
            if (current_id == 12 && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::PROPERTIES)) {
                // Advance past tag
                infile.get();
                PROPERTIES props;
                props.parseProperties(infile);
                itmffile.properties = props;
            }


            if (itmffile.header.hasFlag(ITMF_HEADER_FLAGS::STREAMS_AT_START)) {
                // read streams
                itmffile.stream = CHUNK::ReadChunks(infile);

                // if present, read properties
                peekTag(infile, current_id, current_type);
                if (current_id == 12 && current_type == static_cast<int>(BML_TYPES::OBJECT) && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::PROPERTIES)) {
                    // Advance past tag
                    infile.get();

                    PROPERTIES props;
                    props.parseProperties(infile);
                    itmffile.properties = props;
                }

                // read streamheaders
                if (current_id == 15 && current_type == static_cast<int>(BML_TYPES::OBJECT)) {
                    // Advance past tag
                    infile.get();

                    itmffile.streamheaders = STREAM_HEADER::ReadStreamHeaders(infile);
                }
                else {
                    // TODO: Error: No streamheaders
                }
                // if present, read index
                peekTag(infile, current_id, current_type);
                if (current_id == 14 && current_type == static_cast<int>(BML_TYPES::OBJECT) && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::INDEX)) {
                    // Advance past tag
                    infile.get();

                    itmffile.index = INDEX::ReadIndexes(infile);
                }
                else {
                    // TODO: Error: No indexes
                }

                // if present, read directory
                peekTag(infile, current_id, current_type);
                if (current_id == 13 && current_type == static_cast<int>(BML_TYPES::OBJECT) && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::DIRECTORY)) {
                    // Advance past tag
                    infile.get();

                    itmffile.directory = DIRECTORY::ReadDirectories(infile);
                    // Sync the filelist to match the directories we found
                    itmffile.syncFilelist();
                }
                else {
                    // TODO: Error: No indexes
                }
                // if present, read signature
                peekTag(infile, current_id, current_type);
                if (current_id == 16 && current_type == static_cast<int>(BML_TYPES::OBJECT) && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::SIGNED)) {
                    // Advance past tag
                    infile.get();

                    itmffile.signature->parseSignature(infile);
                }
                else {
                    // TODO: Error: No indexes
                }
                // read footer
                itmffile.footer.parseFooter(infile);

            } else if (itmffile.header.hasFlag(ITMF_HEADER_FLAGS::STREAMS_AT_END)) {
                // properties already read above
                // read streamheaders
                peekTag(infile, current_id, current_type);
                if (current_id == 15 && current_type == static_cast<int>(BML_TYPES::OBJECT)) {
                    // Advance past tag
                    infile.get();

                    itmffile.streamheaders = STREAM_HEADER::ReadStreamHeaders(infile);
                }
                else {
                    // TODO: Error: No streamheaders
                }
                // if present, read index
                peekTag(infile, current_id, current_type);
                if (current_id == 14 && current_type == static_cast<int>(BML_TYPES::OBJECT) && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::INDEX)) {
                    // Advance past tag
                    infile.get();

                    itmffile.index = INDEX::ReadIndexes(infile);
                }
                else {
                    // TODO: Error: No indexes
                }
                // if present, read directory
                peekTag(infile, current_id, current_type);
                if (current_id == 13 && current_type == static_cast<int>(BML_TYPES::OBJECT) && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::DIRECTORY)) {
                    // Advance past tag
                    infile.get();

                    itmffile.directory = DIRECTORY::ReadDirectories(infile);
                }
                else {
                    // TODO: Error: No indexes
                }
                // if present, read signature
                peekTag(infile, current_id, current_type);
                if (current_id == 16 && current_type == static_cast<int>(BML_TYPES::OBJECT) && itmffile.header.hasFlag(ITMF_HEADER_FLAGS::SIGNED)) {
                    // Advance past tag
                    infile.get();

                    itmffile.signature->parseSignature(infile);
                }
                else {
                    // TODO: Error: No indexes
                }
                // read streams
                itmffile.stream = CHUNK::ReadChunks(infile);
            }
            else {
                // TODO: Error: File should be either STREAMS_AT_START or STREAMS_AT_END
            }

        }

        infile.close();

        return itmffile;
    }

    void ITMFFILE::addProperty(std::string key, std::string value) {
        if (!CHECK_BOOST_OPTIONAL(properties)) {
            properties = PROPERTIES();
            config.setPropertiesIncluded(true);
            header.addFlag(ITMF_HEADER_FLAGS::PROPERTIES);
        }
        std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(11, key), BMLstring(12, value));
        properties->addProperty(prop);
    }

    void ITMFFILE::addProperty(std::string key, int64_t value) {
        if (!CHECK_BOOST_OPTIONAL(properties)) {
            properties = PROPERTIES();
            config.setPropertiesIncluded(true);
            header.addFlag(ITMF_HEADER_FLAGS::PROPERTIES);
        }
        std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(11, key), BMLlong(12, value));
        properties->addProperty(prop);
    }

    STREAM_HEADER* ITMFFILE::getStreamHeader(ITMF_STREAM_TYPES stream_type)
    {
        for (auto it = streamheaders.begin(); it != streamheaders.end(); it++) {
            if (stream_type == ITMF_STREAM_TYPES::FILE_DATA) {
                bool found = false;
                boost::variant<BMLint, BMLstring> t = (*it).getType();
                boost::apply_visitor(check_file_stream_header(found), t);
                if (found) {
                    return &(*it);
                }
            }
        }

        return nullptr; 
    }

    void ITMFFILE::addFile(std::string filepath)
    {
        filelist.push_back(filepath);
        std::ifstream infile(filepath, std::ios::in | std::ios::binary);
        infile.seekg(0, std::ios::end);
        std::streampos size = infile.tellg();
        int64_t num_chunks_needed = (size / MAX_CHUNK_SIZE) + 1;

        if (streamheaders.empty()) {
            STREAM_HEADER streamheader("file");
            streamheader.setNumBytes((int64_t)size);
            streamheader.setNumChunks(num_chunks_needed);
            streamheaders.push_back(streamheader);
        }
        else {
            STREAM_HEADER* streamheader = getStreamHeader(ITMF_STREAM_TYPES::FILE_DATA);
            streamheader->addNumBytes((int64_t)size);
            streamheader->addNumChunks(num_chunks_needed);
        }

        infile.close();
    }

    void ITMFFILE::writeFiles(std::ofstream& outfile)
    {
        DIRECTORY file_stream_directory;
        INDEX file_stream_index; // added to indexes if indexes are included

        //char* memblock = new char[MAX_CHUNK_SIZE];
        std::shared_ptr<char> memblock(new char[MAX_CHUNK_SIZE], std::default_delete<char[]>());
        int64_t chunk_index = 0;
        int prev_chunk_size = 0;

        for (auto it = filelist.begin(); it != filelist.end(); it++) {
            int num_chunks = 0;

            std::ifstream infile((*it), std::ios::in | std::ios::binary);
            if (infile.is_open()) {
                std::streampos begin = infile.tellg();
                infile.seekg(0, std::ios::end);
                std::streampos end = infile.tellg();
                infile.seekg(0, std::ios::beg);
                std::cout << (end - begin) << std::endl;

                // create stream properties (one per file)
                STREAM_PROPERTIES file_properties;
                file_properties.setChunkIndex(chunk_index);
                file_properties.setNumBytes(int64_t(end - begin));
                std::size_t found = (*it).find_last_of("/\\");
                std::string file = (*it).substr(found + 1);
                if (file == "project.ocs")
                    file_properties.setName(file);
                else
                    file_properties.setName("assets/" + file);

                // add stream property to directory
                file_stream_directory.addStreamProperty(file_properties);
                
                while (infile) {
                    int pos_delta = 0;

                    infile.read(memblock.get(), MAX_CHUNK_SIZE);
                    size_t bytes_read = infile.gcount();

                    if (!bytes_read)
                        break;

                    BMLblob datablob(7, bytes_read, memblock);
                    CHUNK c(datablob);

                    c.write(outfile);
                    chunk_index++;

                    /*pos_delta += bytes_read;
                    pos_delta += 4;*/
                    file_stream_index.addNumBytes(std::pair<BMLlong, boost::optional<BMLlong>>(BMLlong(6, prev_chunk_size), BMLlong(10, static_cast<int32_t>(bytes_read))));
                    prev_chunk_size = bytes_read;
                    prev_chunk_size += 4;
                }
            }

            infile.close();
        }

        if (config.isIndexIncluded()) {
            index->push_back(file_stream_index);
        }
        directory.push_back(file_stream_directory);
    }

    void ITMFFILE::writeStreamsAtStart(std::ofstream& outfile) {
        header.write(outfile);

        // Properties
        if (config.isPropertiesIncluded()) {
            properties.get().write(outfile);
        }
        // Write files to chunks
        writeFiles(outfile);

        size_t offset_to_stream = 0;
        //// Properties
        //if (config.isPropertiesIncluded()) {
        //    offset_to_stream += properties.get().write(outfile);
        //}

        // Stream Headers
        offset_to_stream += streamheaders[0].writeOpenTag(outfile);
        for (auto it = streamheaders.begin(); it != streamheaders.end(); it++) {
            offset_to_stream += (*it).write(outfile);
        }
        offset_to_stream += streamheaders[0].writeCloseTag(outfile);

        // Index
        if (config.isIndexIncluded()) {

            offset_to_stream += index.get()[0].writeOpenTag(outfile);

            std::vector<INDEX>* index_ptr = index.get_ptr();
            for (auto it = (*index_ptr).begin(); it != (*index_ptr).end(); it++) {
                offset_to_stream += (*it).write(outfile);
            }

            offset_to_stream += index.get()[0].writeCloseTag(outfile);
        }

        // Directory
        offset_to_stream += directory[0].writeOpenTag(outfile);
        for (auto it = directory.begin(); it != directory.end(); it++) {
            offset_to_stream += (*it).write(outfile);
        }
        offset_to_stream += directory[0].writeCloseTag(outfile);

        // Footer
        footer.setOffset(static_cast<uint32_t>(offset_to_stream));
        footer.write(outfile);
    }

    void ITMFFILE::writeStreamsAtEnd(std::ofstream& outfile) {
        header.write(outfile);

        // Properties
        if (config.isPropertiesIncluded()) {
            properties.get().write(outfile);
        }

        // Stream Headers
        streamheaders[0].writeOpenTag(outfile);
        for (auto it = streamheaders.begin(); it != streamheaders.end(); it++) {
            (*it).write(outfile);
        }
        streamheaders[0].writeCloseTag(outfile);

        // Index
        if (config.isIndexIncluded()) {
            index.get()[0].writeOpenTag(outfile);

            std::vector<INDEX>* index_ptr = index.get_ptr();
            for (auto it = (*index_ptr).begin(); it != (*index_ptr).end(); it++) {
                (*it).write(outfile);
            }

            index.get()[0].writeCloseTag(outfile);
        }

        // Directory
        directory[0].writeOpenTag(outfile);
        for (auto it = directory.begin(); it != directory.end(); it++) {
            (*it).write(outfile);
        }
        directory[0].writeCloseTag(outfile);

        // Write files to chunks
        writeFiles(outfile);
    }

    // Set file list to consist of only each name found in the Directories
    void ITMFFILE::syncFilelist() {
        filelist.clear();
        for (DIRECTORY& dir : directory)
            for (STREAM_PROPERTIES& file : dir.getStreamProperties())
                filelist.push_back(file.getName().getValue());
    }

    void ITMFFILE::write(std::string location, std::string filename) // needs to be updated for both encoding types
    {
        std::string filepath = location + '\\' + filename;
        std::ofstream outstream(filepath, std::ios::out | std::ios::binary);
        if (outstream.is_open()) {
            if (config.getEncodingOrder() == ITMF_ENCODING_ORDER::STREAMS_AT_START) {
                writeStreamsAtStart(outstream);
            }
            else if (config.getEncodingOrder() == ITMF_ENCODING_ORDER::STREAMS_AT_END) {
                writeStreamsAtEnd(outstream);
            }
        }
        
        outstream.close();
    }
}