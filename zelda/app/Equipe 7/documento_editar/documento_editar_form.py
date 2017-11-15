from flask_wtf import Form
from wtforms import StringField, TextAreaField
from wtforms.validators import DataRequired

class EditarDocumentoForm(Form):
    documento_tipo = StringField ('Tipo do Documento', validators=[DataRequired('O Tipo do Documento é obrigatório.')])
    documento_caminho = StringField('Caminho', validators=[DataRequired('O Documento precisa de um caminho para ser acessada.')])
    documento_desc = TextAreaField('Descrição')
