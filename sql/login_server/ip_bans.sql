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

 Date: 08/15/2013 18:29:56 PM
*/

-- ----------------------------
--  Table structure for ip_bans
-- ----------------------------
DROP TABLE IF EXISTS "public"."ip_bans";
CREATE TABLE "public"."ip_bans" (
	"ip" text NOT NULL COLLATE "default",
	"ban_end" int8
)
WITH (OIDS=FALSE);
ALTER TABLE "public"."ip_bans" OWNER TO "postgres";

-- ----------------------------
--  Primary key structure for table ip_bans
-- ----------------------------
ALTER TABLE "public"."ip_bans" ADD CONSTRAINT "ip_bans_pkey" PRIMARY KEY ("ip") NOT DEFERRABLE INITIALLY IMMEDIATE;

