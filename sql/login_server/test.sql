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

 Date: 08/15/2013 18:29:51 PM
*/

-- ----------------------------
--  Table structure for test
-- ----------------------------
DROP TABLE IF EXISTS "public"."test";
CREATE TABLE "public"."test" (
	"a" text COLLATE "default",
	"b" text COLLATE "default"
)
WITH (OIDS=FALSE);
ALTER TABLE "public"."test" OWNER TO "postgres";

