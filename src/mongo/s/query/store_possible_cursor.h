/**
 *    Copyright (C) 2015 MongoDB Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once

#include <string>

namespace mongo {

class BSONObj;
class ClusterCursorManager;
template <typename T>
class StatusWith;

namespace executor {
class TaskExecutor;
}  // namespace executor

/**
 * Utility function to create a cursor based on existing cursor on a remote instance.  'cmdResult'
 * must be the response object generated upon creation of the cursor. The newly created cursor will
 * use 'executor' to retrieve batches of results from the shards and is stored with 'cursorManager'
 * (unless 'useClusterClientCursor' is set to false, in which case the cursor is stored with the
 * 'cursorCache' singleton).
 *
 * If 'cmdResult' does not describe a command cursor response document or no cursor is specified,
 * returns 'cmdResult'. If a parsing error occurs, returns an error Status. Otherwise, returns a
 * BSONObj response document describing the newly-created cursor, which is suitable for returning to
 * the client.
 */
StatusWith<BSONObj> storePossibleCursor(const std::string& server,
                                        const BSONObj& cmdResult,
                                        executor::TaskExecutor* executor,
                                        ClusterCursorManager* cursorManager);

}  // namespace mongo
