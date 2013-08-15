/*
 Navicat Premium Data Transfer

 Source Server         : local
 Source Server Type    : PostgreSQL
 Source Server Version : 90204
 Source Host           : localhost
 Source Database       : desperion
 Source Schema         : public

 Target Server Type    : PostgreSQL
 Target Server Version : 90204
 File Encoding         : utf-8

 Date: 08/15/2013 18:30:00 PM
*/

-- ----------------------------
--  Table structure for game_servers
-- ----------------------------
DROP TABLE IF EXISTS "public"."game_servers";
CREATE TABLE "public"."game_servers" (
	"id" int4 NOT NULL,
	"key" text COLLATE "default",
	"players_limit" int2,
	"min_level" int2
)
WITH (OIDS=FALSE);
ALTER TABLE "public"."game_servers" OWNER TO "postgres";

-- ----------------------------
--  Primary key structure for table game_servers
-- ----------------------------
ALTER TABLE "public"."game_servers" ADD CONSTRAINT "game_servers_pkey" PRIMARY KEY ("id") NOT DEFERRABLE INITIALLY IMMEDIATE;

