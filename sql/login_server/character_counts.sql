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

 Date: 08/15/2013 18:30:05 PM
*/

-- ----------------------------
--  Table structure for character_counts
-- ----------------------------
DROP TABLE IF EXISTS "public"."character_counts";
CREATE TABLE "public"."character_counts" (
	"server_id" int2,
	"account_guid" int4
)
WITH (OIDS=FALSE);
ALTER TABLE "public"."character_counts" OWNER TO "postgres";

