from flask_mysqldb import MySQL

class DocumentoInterface:

    def __init__(self, app):
        self.mysql = MySQL(app)

    def execute_query(self, query, insert=False):
        cur = self.mysql.connection.cursor()
        cur.execute(query)
        if insert:
            self.mysql.connection.commit()
        else:
            data = cur.fetchall()
            cur.close()
            return data

    def cadastra_documento(self, documento):
        self.execute_query("insert into documento (documento_tipo, documento_desc, documento_caminho) values ('{}','{}','{}')".format(documento.tipo, documento.desc, documento.caminho), True)
        data = self.execute_query("select documento_id from documento order by documento_id desc limit 1")

        return data[0]["documento_id"]

    def edita_documento(self, documento):
        self.execute_query("update documento set documento_tipo = '{}', documento_desc = '{}', documento_caminho = '{}' where documento_id = '{}'".format(documento.tipo, documento.desc, documento.caminho, documento.get_id()), True)

    def deleta_documento(self, documento_id):
        self.execute_query("delete from documento where documento_id = '{}'".format(documento_id), True)

    def get_documento(self, documento_id):
        data = self.execute_query("select * from documento where documento_id = '{}'".format(documento_id))
        return data

    def get_documento_ids(self):
        data = self.execute_query("select documento_id from documento")
        return data
