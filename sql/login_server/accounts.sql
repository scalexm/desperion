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

 Date: 08/15/2013 18:30:09 PM
*/

-- ----------------------------
--  Table structure for accounts
-- ----------------------------
DROP TABLE IF EXISTS "public"."accounts";
CREATE TABLE "public"."accounts" (
	"guid" int4 NOT NULL,
	"account" text COLLATE "default",
	"password" text COLLATE "default",
	"salt" text COLLATE "default",
	"pseudo" text COLLATE "default",
	"level" int2,
	"secret_question" text COLLATE "default",
	"secret_answer" text COLLATE "default",
	"logged" int2,
	"last_server" int2,
	"subscription_end" int8,
	"ban_end" int8,
	"ticket" text COLLATE "default"
)
WITH (OIDS=FALSE);
ALTER TABLE "public"."accounts" OWNER TO "postgres";

-- ----------------------------
--  Primary key structure for table accounts
-- ----------------------------
ALTER TABLE "public"."accounts" ADD CONSTRAINT "accounts_pkey" PRIMARY KEY ("guid") NOT DEFERRABLE INITIALLY IMMEDIATE;

