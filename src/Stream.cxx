/** \file Stream.cxx
    \brief Implementation of OStream class.
    \author James Peachey, HEASARC/GSSC
*/
#include "st_stream/Stream.h"
#include "st_stream/st_stream.h"

namespace st_stream {

  // Define standard streams with maximum chatter set to the highest possible value so that
  // all output sent directly to them will always be displayed.
  OStream sterr(false);
  OStream stlog(false);
  OStream stout(false);

  void OStream::initStdStreams() {
    // Connect standard streams to their natural STL counterparts.
    sterr.connect(std::cerr);
    stlog.connect(std::clog);
    stout.connect(std::cout);
  }

  OStream::OStream(bool use_chatter): m_std_stream_cont(), m_stream_cont(), m_prefix(), m_chat_level(0),
    m_enabled(true), m_use_chatter(use_chatter) { setChatLevel(m_chat_level); }

  auto OStream::prefix() -> OStream & { return *this << m_prefix; }

  auto OStream::setChatLevel(unsigned int chat_level) -> OStream & {
    m_chat_level = chat_level;
    if (m_use_chatter) enable(m_chat_level <= GetMaximumChatter());
    return *this;
  }

  auto OStream::getPrefix() const -> const std::string & { return m_prefix; }

  void OStream::setPrefix(const std::string prefix) { m_prefix = prefix; }

  void OStream::connect(std::ostream & dest) { m_std_stream_cont.insert(&dest); }

  void OStream::disconnect(std::ostream & dest) { m_std_stream_cont.erase(&dest); }

  void OStream::connect(OStream & dest) { if (this != &dest) m_stream_cont.insert(&dest); }

  void OStream::disconnect(OStream & dest) { m_stream_cont.erase(&dest); }

  auto OStream::flags() const -> std::ios_base::fmtflags {
    return getStreamState<std::ios_base::fmtflags, std::ios_base>(&std::ostream::flags, &OStream::flags);
  }

  auto OStream::flags(std::ios_base::fmtflags fmtfl) -> std::ios_base::fmtflags {
    return setStreamState<std::ios_base::fmtflags, std::ios_base>(&std::ostream::flags, &OStream::flags, &OStream::flags, fmtfl);
  }

  auto OStream::setf(std::ios_base::fmtflags fmtfl) -> std::ios_base::fmtflags {
    return setStreamState<std::ios_base::fmtflags, std::ios_base>(&std::ostream::setf, &OStream::setf, &OStream::flags, fmtfl);
  }

  // Note that the following method has an unusal signature and thus can't use setStreamState.
  auto OStream::setf(std::ios_base::fmtflags fmtfl, std::ios_base::fmtflags mask) -> std::ios_base::fmtflags {
    std::ios_base::fmtflags orig_flags = flags();

    // Only modify destination streams if message chatter is less than or equal to maximum user/client chatter.
    if (m_enabled) {
      // Call setf for all std::ostream objects.
      for (StdStreamCont_t::iterator itor = m_std_stream_cont.begin(); itor != m_std_stream_cont.end(); ++itor)
        (*itor)->setf(fmtfl, mask);

      // Call setf for all OStream objects.
      for (OStreamCont_t::iterator itor = m_stream_cont.begin(); itor != m_stream_cont.end(); ++itor)
        (*itor)->setf(fmtfl, mask);
    }

    return orig_flags;
  }

  // Note that the following method has an unusal signature and thus can't use setStreamState.
  void OStream::unsetf(std::ios_base::fmtflags mask) {
    // Only modify destination streams if message chatter is less than or equal to maximum user/client chatter.
    if (m_enabled) {
      // Call unsetf for all std::ostream objects.
      for (StdStreamCont_t::iterator itor = m_std_stream_cont.begin(); itor != m_std_stream_cont.end(); ++itor)
        (*itor)->unsetf(mask);

      // Call unsetf for all OStream objects.
      for (OStreamCont_t::iterator itor = m_stream_cont.begin(); itor != m_stream_cont.end(); ++itor)
        (*itor)->unsetf(mask);
    }
  }

  auto OStream::precision() const -> std::streamsize {
    return getStreamState<std::streamsize, std::ios_base>(&std::ostream::precision, &OStream::precision);
  }

  auto OStream::precision(std::streamsize new_precision) -> std::streamsize {
    return setStreamState<std::streamsize, std::ios_base>(&std::ostream::precision, &OStream::precision,
      &OStream::precision, new_precision);
  }

  auto OStream::width() const -> std::streamsize {
    return getStreamState<std::streamsize, std::ios_base>(&std::ostream::width, &OStream::width);
  }

  auto OStream::width(std::streamsize new_width) -> std::streamsize {
    return setStreamState<std::streamsize, std::ios_base>(&std::ostream::width, &OStream::width, &OStream::width, new_width);
  }

  auto OStream::fill() const -> char {
    char orig = char();

    if ( !m_std_stream_cont.empty() )
      orig = ( *m_std_stream_cont.begin() )->fill();

    else if ( !m_stream_cont.empty() )
      orig = ( *m_stream_cont.begin() )->fill();

    return orig;
  }

  auto OStream::fill( char new_fill ) -> char {

    // Return value is the current value of this particular stream property.
    char orig = this->fill();

    // Only modify destination streams if message chatter is less than or equal
    // to maximum user/client chatter.
    if ( m_enabled ) {
      for ( auto& strm : m_std_stream_cont )
        strm->fill( new_fill );
      for ( auto& strm : m_stream_cont )
        strm->fill( new_fill );
  }

    return orig;
  }

  auto prefix(OStream & os) -> OStream & { return os.prefix(); }
}
