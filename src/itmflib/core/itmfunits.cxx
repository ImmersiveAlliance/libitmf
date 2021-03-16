#include <itmfunits.h>

namespace itmflib {
	ITMF_HEADER ITMF_HEADER::CreateITMFHeader(int32_t flags)
	{
		return ITMF_HEADER(BMLstring(1, "OX"), BMLint(2, 1), BMLint(3, flags));
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

	size_t STREAM_PROPERTIES::write(std::ofstream& outfile)
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

	size_t DIRECTORY::write(std::ofstream& outfile)
	{
		size_t bytes_written = 0;

		bytes_written += writeOpenTag(outfile);

		if (CHECK_BOOST_OPTIONAL(stream_index))
			bytes_written += stream_index.get().save(outfile);

		for (STREAM_PROPERTIES& prop : stream_properties) {
			bytes_written += prop.write(outfile);
		}

		bytes_written += writeCloseTag(outfile);

		return bytes_written;
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

	void ITMF_FOOTER::write(std::ofstream& outfile)
	{
		outfile.write((char*)&offset_to_stream_end, sizeof(offset_to_stream_end));
		outfile.write((char*)&magic, sizeof(magic));
	}
}