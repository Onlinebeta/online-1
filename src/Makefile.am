DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

ONLINE_CONFIG_INCLUDES=-I$(builddir)/config
ONLINE_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

ONLINE_INCLUDES += -I$(srcdir)/secp256k1/include

LIBONLINE_SERVER=libonline_server.a
LIBONLINE_WALLET=libonline_wallet.a
LIBONLINE_COMMON=libonline_common.a
LIBONLINE_CLI=libonline_cli.a
LIBONLINE_UTIL=libonline_util.a
LIBONLINE_CRYPTO=crypto/libonline_crypto.a
LIBONLINE_UNIVALUE=univalue/libonline_univalue.a
LIBONLINEQT=qt/libonlineqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libonline_crypto.a \
  libonline_util.a \
  libonline_common.a \
  univalue/libonline_univalue.a \
  libonline_server.a \
  libonline_cli.a
if ENABLE_WALLET
ONLINE_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libonline_wallet.a
endif

if BUILD_ONLINE_LIBS
lib_LTLIBRARIES = libonlineconsensus.la
LIBONLINE_CONSENSUS=libonlineconsensus.la
else
LIBONLINE_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_ONLINED
  bin_PROGRAMS += onlined
endif

if BUILD_ONLINE_UTILS
  bin_PROGRAMS += online-cli online-tx
endif

.PHONY: FORCE
# online core #
ONLINE_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  amount.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compressor.h \
  primitives/block.h \
  primitives/transaction.h \
  core_io.h \
  crypter.h \
  db.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  pow.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script/interpreter.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/script_error.h \
  serialize.h \
  streams.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilstrencodings.h \
  utilmoneystr.h \
  utiltime.h \
  version.h \
  wallet.h \
  wallet_ismine.h \
  walletdb.h \
  compat/sanity.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libonline_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between onlined and online-qt
libonline_server_a_CPPFLAGS = $(ONLINE_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libonline_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(ONLINE_CORE_H)

# wallet: shared between onlined and online-qt, but only linked
# when wallet enabled
libonline_wallet_a_CPPFLAGS = $(ONLINE_INCLUDES)
libonline_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  wallet_ismine.cpp \
  walletdb.cpp \
  $(ONLINE_CORE_H)

# crypto primitives library
crypto_libonline_crypto_a_CPPFLAGS = $(ONLINE_CONFIG_INCLUDES)
crypto_libonline_crypto_a_SOURCES = \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/rfc6979_hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/rfc6979_hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/sha1.h \
  crypto/ripemd160.h

# univalue JSON library
univalue_libonline_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp \
  univalue/univalue_escapes.h \
  univalue/univalue.h

# common: shared between onlined, and online-qt and non-server tools
libonline_common_a_CPPFLAGS = $(ONLINE_INCLUDES)
libonline_common_a_SOURCES = \
  allocators.cpp \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  $(ONLINE_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libonline_util_a_CPPFLAGS = $(ONLINE_INCLUDES)
libonline_util_a_SOURCES = \
  compat/strnlen.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  random.cpp \
  rpcprotocol.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilstrencodings.cpp \
  utilmoneystr.cpp \
  utiltime.cpp \
  $(ONLINE_CORE_H)

if GLIBC_BACK_COMPAT
libonline_util_a_SOURCES += compat/glibc_compat.cpp
libonline_util_a_SOURCES += compat/glibcxx_compat.cpp
endif

# cli: shared between online-cli and online-qt
libonline_cli_a_CPPFLAGS = $(ONLINE_INCLUDES)
libonline_cli_a_SOURCES = \
  rpcclient.cpp \
  $(ONLINE_CORE_H)

nodist_libonline_util_a_SOURCES = $(srcdir)/obj/build.h
#

# onlined binary #
onlined_LDADD = \
  $(LIBONLINE_SERVER) \
  $(LIBONLINE_COMMON) \
  $(LIBONLINE_UNIVALUE) \
  $(LIBONLINE_UTIL) \
  $(LIBONLINE_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
onlined_LDADD += libonline_wallet.a
endif
onlined_SOURCES = onlined.cpp
#

if TARGET_WINDOWS
onlined_SOURCES += onlined-res.rc
endif

onlined_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
onlined_CPPFLAGS = $(ONLINE_INCLUDES)
onlined_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# online-cli binary #
online_cli_LDADD = \
  $(LIBONLINE_CLI) \
  $(LIBONLINE_UTIL) \
  $(BOOST_LIBS) \
  $(SSL_LIBS) \
  $(CRYPTO_LIBS)

online_cli_SOURCES = \
  online-cli.cpp

online_cli_CPPFLAGS = $(ONLINE_INCLUDES)
#

# online-tx binary #
online_tx_LDADD = \
  $(LIBONLINE_UNIVALUE) \
  $(LIBONLINE_COMMON) \
  $(LIBONLINE_UTIL) \
  $(LIBONLINE_CRYPTO) \
  $(LIBSECP256K1) \
  $(BOOST_LIBS) \
  $(CRYPTO_LIBS)

online_tx_SOURCES = online-tx.cpp
online_tx_CPPFLAGS = $(ONLINE_INCLUDES)
#
online_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
online_cli_SOURCES += online-cli-res.rc
endif
online_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if BUILD_ONLINE_LIBS
include_HEADERS = script/onlineconsensus.h
libonlineconsensus_la_SOURCES = \
  primitives/transaction.cpp \
  crypto/hmac_sha512.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/ripemd160.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  pubkey.cpp \
  script/script.cpp \
  script/interpreter.cpp \
  script/onlineconsensus.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libonlineconsensus_la_SOURCES += compat/glibc_compat.cpp
  libonlineconsensus_la_SOURCES += compat/glibcxx_compat.cpp
endif

libonlineconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libonlineconsensus_la_LIBADD = $(CRYPTO_LIBS)
libonlineconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_ONLINE_INTERNAL
if USE_LIBSECP256K1
libonlineconsensus_la_LIBADD += secp256k1/libsecp256k1.la
endif
endif

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
