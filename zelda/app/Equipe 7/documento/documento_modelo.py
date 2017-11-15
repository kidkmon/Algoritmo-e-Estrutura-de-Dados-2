from ....cursor import db
from app import app

class Documento:

    def __init__(self, documento_id=None):

        self.__documento_id = None
        self.documento_tipo = None
        self.documento_desc = None
        self.documento_caminho = None
        if documento_id is not None:
            data = db.get_documento(documento_id)
            if data is not None:
                self.__documento_id = documento_id
                self.documento_tipo = data[0]['documento_tipo']
                self.documento_desc = data[0]['documento_desc']
                self.documento_caminho = data[0]['documento_caminho']

    def get_id(self):
        return self.__documento_id

    def get_documento_tipo(self):
        return self.documento_tipo

    def get_documento_desc(self):
        return self.documento_desc

    def deleta(self):
        if self.get_id() is not None:
            db.deleta_documento(self.get_id())

    def salva(self):
        if self.get_id() is None:
            self.__documento_id = db.cadastra_documento(self)
        else:
            db.edita_documento(self)
