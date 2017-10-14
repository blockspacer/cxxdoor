#include "usuario.h"
#include "booking.h"
#include <gtest/gtest.h>
#include <glog/logging.h>
#include "dbmanager.h"
TEST(Usuario, crear_usuario) {
    cxxdoor::Usuario u;
    u.setEmail("mail");
    u.setNombre("vicotr");
    u.setId(cxxdoor::RocksEntity::generateId());
    LOG(INFO) << "rocksdb key: " << u.rocksdb_key().get();
}

TEST(Usuario, guardar_usuario) {
    cxxdoor::Usuario u;
    u.setEmail("mail");
    u.setNombre("vicotr");
    u.setId(cxxdoor::RocksEntity::generateId());
    LOG(INFO) << "rocksdb key: " << u.rocksdb_key().get();
    cxxdoor::DbManager::getInstance()->save<cxxdoor::Usuario>(u);
}
TEST(Usuario, cargar_usuario) {
    cxxdoor::Usuario u;
    u.setEmail("mail");
    u.setNombre("vicotr");
    u.setPassword("thisisapassword");
    u.setId(cxxdoor::RocksEntity::generateId());
    LOG(INFO) << "rocksdb key: " << u.rocksdb_key().get();
    std::string key = u.rocksdb_key().get();
    cxxdoor::DbManager::getInstance()->save<cxxdoor::Usuario>(u);

    cxxdoor::Usuario u2;
    cxxdoor::DbManager::getInstance()->load<cxxdoor::Usuario>(key, u2);
    LOG(INFO) << u2;
}


TEST(Booking, test1) {
    std::shared_ptr<cxxdoor::Usuario> u = std::make_shared<cxxdoor::Usuario>();
    u->setEmail("booker@booking.com");
    u->setNombre("Victor Booking");
    u->setPassword("thisisapassword");
    u->setId(cxxdoor::RocksEntity::generateId());
    LOG(INFO) << "rocksdb key: " << u->rocksdb_key().get();
    std::string key = u->rocksdb_key().get();
    cxxdoor::DbManager::getInstance()->save<cxxdoor::Usuario>(*u);

    std::shared_ptr<cxxdoor::Usuario> u2 = std::make_shared<cxxdoor::Usuario>();
    cxxdoor::DbManager::getInstance()->load<cxxdoor::Usuario>(key, *u2);
    LOG(INFO) << *u2;

    cxxdoor::Booking b;
    cxxdoor::Booking b2;
    b.setUsuario(u2);
    b.setFrom(boost::gregorian::from_simple_string("2017-12-24"));
    b.setTo(boost::gregorian::from_simple_string("2018-1-10"));
    b.setId(cxxdoor::RocksEntity::generateId());
    key = b.rocksdb_key().get();

    cxxdoor::DbManager::getInstance()->save<cxxdoor::Booking>(b);
    cxxdoor::DbManager::getInstance()->load<cxxdoor::Booking>(key, b2);
    LOG(INFO) << b2;
}
