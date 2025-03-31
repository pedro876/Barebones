bl_info = {
    "name": "Barebones FBX Exporter",
    "blender": (4, 0, 0),  # Set to the appropriate version you are using
    "category": "Import-Export",
    "author": "Pedro Casas Martinez",
    "description": "Barebones FBX Exporter",
    "version": (1, 0),
    "support": "COMMUNITY",
}

import bpy
import os
import csv

class BarebonesFBXExporter(bpy.types.Operator):
    """Barebones FBX Exporter"""
    bl_idname = "export.barebones_fbx"
    bl_label = "Barebones FBX Exporter"
    bl_options = {'REGISTER', 'UNDO'}
    
    def execute(self, context):
        export_settings = context.scene.barebones_fbx_settings
        self.export_fbx(export_settings)
        return {'FINISHED'}
    
    def export_fbx(self, export_settings):
        filepath = export_settings.filepath;
        if filepath.startswith("//"):
            filepath = bpy.path.abspath(filepath)
        os.makedirs(os.path.dirname(filepath), exist_ok=True)
        
        directory = os.path.dirname(filepath)
        self.export_lights(filepath)
        self.export_materials(directory)
        
        bpy.ops.export_scene.fbx(
            path_mode = 'RELATIVE',
            filepath=filepath,
            check_existing=False,
            use_selection=export_settings.export_selected,
            apply_unit_scale=True,
            use_space_transform=True,
            global_scale=0.01,
            axis_forward='-Z',
            axis_up='Y',
            bake_space_transform=True
        )
        
        self.report({'INFO'}, f"Exported FBX to: {filepath}")
        print(f"Exported FBX to: {filepath}")
    
    def export_lights(self, filepath):
        def format_float(value):
            return f"{value:.5f}"
        #filepath = os.path.join(directory, f"TestRoom.lights")ç
        filepath = os.path.splitext(filepath)[0]+'.lights'
        anyWrite = False
        with open(filepath, mode='w', newline='') as file:
            writer = csv.writer(file, delimiter=';')
            writer.writerow(["Name", "Range", "Intensity", "Color.r", "Color.g", "Color.b"])
            for obj in bpy.data.objects:
                if obj.type == 'LIGHT':
                    light = obj.data
                    print(f"Writing properties for {obj.name}")
                    range = format_float(light.cutoff_distance)
                    intensity = format_float(light.energy * 0.1 if light.type == 'SUN' else light.energy *2.0 / 1000.0)
                    colorR = format_float(light.color.r)
                    colorG = format_float(light.color.g)
                    colorB = format_float(light.color.b)
                    writer.writerow([obj.name, range, intensity, colorR, colorG, colorB])
                    anyWrite = True
        if not anyWrite:
            if os.path.exists(filepath):
                os.remove(filepath)
                
    
    def export_materials(self, directory):
        def format_float(value):
            return f"{value:.5f}"
        
        print(f"Will export materials to {directory}")
        for mat in bpy.data.materials:
            custom_props = {k: v for k, v in mat.items() if k not in "_RNA_UI"}
            
            filepath = os.path.join(directory, f"{mat.name}.mat")
            anyWrite = False
            print(f"Writing custom properties for {mat.name}")
            with open(filepath, mode='w', newline='') as file:
                writer = csv.writer(file, delimiter=';')
                for key, value in custom_props.items():
                    wroteKey = True
                    if type(value) == str:
                        writer.writerow(["String", key, value])
                    elif type(value) == float:
                        writer.writerow(["Float", key, format_float(value)])
                    elif type(value) == int:
                        writer.writerow(["Integer", key, value])
                    elif type(value) == bool:
                        writer.writerow(["Boolean", key, value])
                    elif hasattr(value, "to_list"):
                        value_list = value.to_list()
                        if value.typecode == 'f' or value.typecode == 'd':
                            formatted_values = [format_float(v) for v in value_list]
                            writer.writerow(["FloatArray", key] + formatted_values)
                        elif value.typecode == 'i':
                            writer.writerow(["IntegerArray", key] + value_list)
                        elif value.typecode == 'b':
                            writer.writerow(["BooleanArray", key] + value_list)
                        else:
                            writer.writerow(["UnsupportedArray", key, str(value_list)])
                    else:
                        writer.writerow(["Unsupported", key, str(value)])
                        wroteKey = False
                    anyWrite = anyWrite or wroteKey
                # Check if there are textures in the material's nodes
                if mat.use_nodes and mat.node_tree:
                    for node in mat.node_tree.nodes:
                        if node.type == 'TEX_IMAGE':  # Check if the node is a texture
                            image = node.image
                            if image:
                                self.report({'INFO'}, f"Texture detected at {mat.name}: {node.name}")
                                texture_path = image.filepath
                                writer.writerow(["Texture2D", node.name, texture_path])
                                anyWrite = True
            if not anyWrite:
                if os.path.exists(filepath):
                    os.remove(filepath)

class BarebonesFBXSettings(bpy.types.PropertyGroup):
    filepath: bpy.props.StringProperty(name="FBX File Path", subtype='FILE_PATH')
    export_selected: bpy.props.BoolProperty(name="Export Selected Objects", default=False)

# UI Panel
class BAREBONES_PT_FBXExporterPanel(bpy.types.Panel):
    """Creates a panel in the Scene properties"""
    bl_label = "Barebones FBX Exporter"
    bl_idname = "BAREBONES_PT_fbx_exporter"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Barebones FBX Export"
    
    def draw(self, context):
        layout = self.layout
        export_settings = context.scene.barebones_fbx_settings
        
        layout.prop(export_settings, "filepath")
        layout.prop(export_settings, "export_selected")
        layout.separator()
        layout.operator("export.barebones_fbx", text="Export FBX")

# Register classes
def register():
    bpy.utils.register_class(BarebonesFBXExporter)
    bpy.utils.register_class(BarebonesFBXSettings)
    bpy.utils.register_class(BAREBONES_PT_FBXExporterPanel)
    bpy.types.Scene.barebones_fbx_settings = bpy.props.PointerProperty(type=BarebonesFBXSettings)

def unregister():
    bpy.utils.unregister_class(BarebonesFBXExporter)
    bpy.utils.unregister_class(BarebonesFBXSettings)
    bpy.utils.unregister_class(BAREBONES_PT_FBXExporterPanel)
    del bpy.types.Scene.barebones_fbx_settings

if __name__ == "__main__":
    register()