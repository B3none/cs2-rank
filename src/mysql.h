#pragma once

#include "abstract.h"
#include <vendor/mysql/include/mysql_mm.h>
#include "player.h"
#include <map>

// CONFIG REQUESTS 

#define CREATE_CONFIG_TABLE "CREATE TABLE IF NOT EXISTS `cs2_rank_configs` ( \
  `id` BIGINT(64) NOT NULL, \
  `version` varchar(32) NOT NULL, \
  UNIQUE INDEX `id` (`id`) USING BTREE) \
  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;"

#define UPDATE_CONFIG_TABLE "INSERT INTO cs2_rank_configs (id, version) \
  VALUES (1, '%s') \
  ON DUPLICATE KEY UPDATE version = VALUES(version);"

// MAP REQUESTS 

#define CREATE_MAPS_TABLE "CREATE TABLE IF NOT EXISTS `cs2_rank_maps` ( \
  `id` BIGINT(64) NOT NULL AUTO_INCREMENT, \
  `name` varchar(32) NOT NULL, \
  UNIQUE INDEX `id` (`id`) USING BTREE) \
  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;"

#define SELECT_MAP "SELECT `id` FROM `cs2_rank_maps` WHERE `name` = '%s'"

#define INSERT_MAP "INSERT INTO `cs2_rank_maps` (`name`) VALUES ('%s');"

// REFERENCE REQUESTS

#define CREATE_REFERENCES_TABLE "CREATE TABLE IF NOT EXISTS `cs2_rank_references` ( \
  `id` BIGINT(64) NOT NULL AUTO_INCREMENT, \
  `reference` varchar(32) NOT NULL, \
  `custom_name` varchar(64), \
  UNIQUE INDEX `id` (`id`) USING BTREE) \
  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;"

#define SELECT_REFERENCE "SELECT `id` FROM `cs2_rank_references` WHERE `reference` = '%s'"

#define INSERT_REFERENCE "INSERT INTO `cs2_rank_references` (`reference`) VALUES ('%s');"

// USERS REQUEST

#define CREATE_USERS_TABLE "CREATE TABLE IF NOT EXISTS `cs2_rank_users` ( \
  `id` BIGINT(64) NOT NULL AUTO_INCREMENT, \
  `authid` BIGINT(64) NOT NULL DEFAULT '0', \
  `name` varchar(32) NOT NULL, \
  `ignore_annouce` INT(11) NOT NULL DEFAULT 0, \
  `lastconnect` int(11) NOT NULL DEFAULT 0, \
  UNIQUE INDEX `id` (`id`) USING BTREE) \
  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;"

#define INSERT_USER "INSERT INTO `cs2_rank_users` (`authid`, `name` ) VALUES ('%lli', '%s');"

#define UPDATE_USER "UPDATE `cs2_rank_users` SET `name` = '%s', `ignore_annouce` = %d, \
 `lastconnect` = %ld WHERE `authid` = '%lli';"

#define SELECT_USER "SELECT `id`, `ignore_annouce` FROM `cs2_rank_users` WHERE `authid` = '%lli'"

// STATS REQUEST

#define CREATE_STATS_TABLE "CREATE TABLE IF NOT EXISTS `cs2_rank_stats` ( \
  `id` BIGINT(64) NOT NULL AUTO_INCREMENT, \
  `user_id` BIGINT(64) NOT NULL DEFAULT '0', \
  `reference` varchar(32) NOT NULL, \
  `map` int(11) NOT NULL, \
  `points` int(11) NOT NULL DEFAULT 0, \
  `death_suicide` int(11) NOT NULL DEFAULT 0, \
  `death_t` int(11) NOT NULL DEFAULT 0, \
  `death_ct` int(11) NOT NULL DEFAULT 0, \
  `bomb_planted` int(11) NOT NULL DEFAULT 0, \
  `bomb_exploded` int(11) NOT NULL DEFAULT 0, \
  `bomb_defused` int(11) NOT NULL DEFAULT 0, \
  `kill_knife` int(11) NOT NULL DEFAULT 0, \
  `kill_headshot` int(11) NOT NULL DEFAULT 0, \
  `kill_t` int(11) NOT NULL DEFAULT 0, \
  `kill_ct` int(11) NOT NULL DEFAULT 0, \
  `teamkill_ct` int(11) NOT NULL DEFAULT 0, \
  `teamkill_t` int(11) NOT NULL DEFAULT 0, \
  `killassist_t` int(11) NOT NULL DEFAULT 0, \
  `killassist_ct` int(11) NOT NULL DEFAULT 0, \
  UNIQUE INDEX `id` (`id`) USING BTREE) \
  ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;"

#define INSERT_STATS "INSERT INTO `cs2_rank_stats` (`user_id`, `reference`, `map` ) VALUES ('%d', '%s', '%d');"

#define UPDATE_STATS "\
UPDATE `cs2_rank_stats` \
SET \
    `points` = %d, \
    `death_suicide` = %d, \
    `death_t` = %d, \
    `death_ct` = %d, \
    `bomb_planted` = %d, \
    `bomb_exploded` = %d, \
    `bomb_defused` = %d, \
    `kill_knife` = %d, \
    `kill_headshot` = %d, \
    `kill_t` = %d, \
    `kill_ct` = %d, \
    `teamkill_t` = %d, \
    `teamkill_ct` = %d, \
    `killassist_t` = %d, \
    `killassist_ct` = %d \
WHERE \
    `user_id` = '%d' AND \
    `reference` = '%s' AND \
    `map` = %i;"

#define SELECT_STATS_MAP "\
SELECT \
    `points`, \
    `death_suicide`, \
    `death_t`, \
    `death_ct`, \
    `bomb_planted`, \
    `bomb_exploded`, \
    `bomb_defused`, \
    `kill_knife`, \
    `kill_headshot`, \
    `kill_t`, \
    `kill_ct`, \
    `teamkill_t`, \
    `teamkill_ct`, \
    `killassist_t`, \
    `killassist_ct` \
FROM \
    `cs2_rank_stats` \
WHERE \
    `user_id` = '%i' AND \
    `reference` = '%s' AND \
    `map` = %i"

#define SELECT_STATS_GLOBAL "\
SELECT \
    SUM(points) AS total_points, \
    SUM(death_suicide) AS total_death_suicide, \
    SUM(death_t) AS total_death_t, \
    SUM(death_ct) AS total_death_ct, \
    SUM(bomb_planted) AS total_bomb_planted, \
    SUM(bomb_exploded) AS total_bomb_exploded, \
    SUM(bomb_defused) AS total_bomb_defused, \
    SUM(kill_knife) AS total_kill_knife, \
    SUM(kill_headshot) AS total_kill_headshot, \
    SUM(kill_t) AS total_kill_t, \
    SUM(kill_ct) AS total_kill_ct, \
    SUM(teamkill_t) AS total_teamkill_t, \
    SUM(teamkill_ct) AS total_teamkill_ct, \
    SUM(killassist_t) AS total_killassist_t, \
    SUM(killassist_ct) AS total_killassist_ct \
FROM \
    cs2_rank_stats \
WHERE \
    user_id = '%i' AND \
    `reference` = '%s' \
GROUP BY \
    user_id;"

// RANK REQUEST

#define TOP_GLOBAL "\
SELECT \
    cu.name, \
    SUM(cr.points) AS total_points \
FROM \
    cs2_rank_stats cr \
    JOIN cs2_rank_users cu ON cr.user_id = cu.id \
WHERE \
    cr.`reference` = '%s' \
GROUP BY \
    cr.user_id \
HAVING \
    SUM(cr.points) >= %i \
ORDER BY \
    SUM(cr.points) DESC \
LIMIT 15;"

#define RANK_GLOBAL "\
SELECT \
    COUNT(DISTINCT user_id) as count \
FROM \
    (SELECT \
        user_id, \
        SUM(points) as total_points \
    FROM \
        cs2_rank_stats \
    WHERE \
        `reference` = '%s' \
    GROUP BY \
        user_id) AS subquery \
WHERE \
    total_points > %i;"

#define TOP_MAP "\
SELECT \
    cu.name, \
    cr.points \
FROM \
    cs2_rank_stats cr \
    JOIN cs2_rank_users cu ON cr.user_id = cu.id \
WHERE \
    points >= %i AND \
    `reference` = '%s' AND \
    `map` = %i \
ORDER BY \
    points DESC \
LIMIT 15;"

#define RANK_MAP "\
SELECT \
    COUNT(*) \
FROM \
    `cs2_rank_stats` \
WHERE \
    `points` > %i AND \
    `reference` = '%s' AND \
    `map` = %i;"

#define REMOVE_USER_FROM_OTHERMAPS "DELETE FROM `cs2_rank_stats` WHERE `user_id` = '%i' AND `reference` = '%s' AND `map` != %i"

extern IVEngineServer2 *g_pEngine;
extern IMySQLClient *g_pMysqlClient;
extern IMySQLConnection *g_pConnection;

class CRankPlayer;

class CMysql
{
public:
  CMysql()
  {
    Connect();
  }

public:
  void Destroy();

  void CreateDatabaseIfNotExist();

  bool IsConnected() { return m_bConnected; };

  void UpdateUser(CRankPlayer *pPlayer);
  void GetUser(CRankPlayer *pPlayer);
  void RemoveFromOtherMap(CRankPlayer *pPlayer);

  void GetTopPlayers(bool global, std::function<void(std::map<std::string, int>)> callback);
  void GetRank(bool global, CRankPlayer *pPlayer, std::function<void(int)> callback);

private:
  int g_iMapId;
  bool m_bConnected;

  void Connect();

  std::string Escape(const char *value);

  void GetUserStats(CRankPlayer *pPlayer);

  void Query_GetRankReference(IMySQLQuery *cb);
  void Query_GetUser(IMySQLQuery *cb, CRankPlayer *pPlayer);
  void Query_GetUserStatsMap(IMySQLQuery *cb, CRankPlayer *pPlayer);
  void Query_GetUserStatsGlobal(IMySQLQuery *cb, CRankPlayer *pPlayer);
  void Query_TopPlayers(IMySQLQuery *cb, std::function<void(std::map<std::string, int>)> callback);
  void Query_Rank(IMySQLQuery *cb, std::function<void(int)> callback);
  void Query_GetMapId(IMySQLQuery *cb);
  void Query_CreateMap();
  void Query_CreateReference();
  void Query_UpdateConfigTable();
};

extern CMysql *g_CMysql;